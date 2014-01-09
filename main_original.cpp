#include <allegro.h>
#include <cstdlib> 
#include <time.h>

#include "game.h"
#include "objects.h"
#include "goodie.h"



int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    //create new classes
    //--------------------------------------------------------------------------
    
    
    int dir;
    int fire=0; 
    int laserdir,p,q;
    int count=0;
    int loader = 0;
    int maxEnemies;
    bool move;
    bool isCollide;
    bool isCrashed;
    int deadRobot=0;
    int enemyXplode = 51;
    int showRip=100;
    int changingLevel = 101;
    
    maxEnemies=100;
    
    //--------------------------------------------------------------------------
    //create new classes
    //--------------------------------------------------------------------------
    Game myGame;
    myGame.SetUpGame();
        
    Goodie playerRobot;
    playerRobot.LoadObject("goodrobot.bmp");

    Goodie laser;
    laser.LoadObject("laserbeam.bmp");    

    Objects baddieHouse;
    baddieHouse.LoadObject("robothouse.bmp"); 

    Objects rip;
    rip.LoadObject("rip.bmp"); 

    Objects xplode;
    xplode.LoadObject("blasted.bmp"); 

    Objects nextLevel;
    nextLevel.LoadObject("levelComplete.bmp"); 

    Objects gameLost;
    gameLost.LoadObject("gameoverdied.bmp"); 

    Objects gameWon;
    gameWon.LoadObject("gameoverwon.bmp");     
    
    Objects badRobot[maxEnemies];
    
    for(int r=0;r<=maxEnemies;r++)
    {
            badRobot[r].LoadObject("badrobot.bmp");
    }
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    
    
    maxEnemies = myGame.GetLevel();
    myGame.InitScreen();
       
    while(!key[KEY_ESC])
    {
            deadRobot=0;
            //draw baddy robots
           
           
            for(int r=0;r<=maxEnemies;r++)
            {  
                    if(badRobot[r].GetAlive()== true)
                    {
                          myGame.DrawPicturetoBuffer(badRobot[r].GetObject(),badRobot[r].GetObjectX(),badRobot[r].GetObjectY());
                    }
                    else
                    {
                                                                                                                                                        
                         if(deadRobot==maxEnemies)
                         {
                                  myGame.LoadGame(3); 
                                  myGame.DrawBuffertoScreen();
                                                                    
                                  int oldlevel = myGame.GetLevel();
                                  int newlevel = oldlevel+1;
                                  myGame.SetLevel(newlevel);
                                  maxEnemies = newlevel;
                             
    
                                  for(int r=0;r<=maxEnemies;r++)
                                  {
                                            badRobot[r].SetAlive(true);
                                  }
                                  
                                 
                                  changingLevel = 0;
                
                         }  
                         deadRobot++;
                    }      
            }             
                        
           move = false;             
           
           if(loader<1000)
           {
                  myGame.LoadGame(1);
                  loader++;
           }
           else if((loader>=1000)&&(loader<1500))
           {
                  myGame.LoadGame(2);
                  loader++;
           }
           else
           {
               if(count == 7)
               {
                        
                        for(int r=0;r<=maxEnemies;r++)
                        {
                            //random move
                            badRobot[r].AIMove(0);
                        }         
                        count=0;
               }
               count++;
             
            if((key[KEY_RIGHT])&&(key[KEY_UP])) //northeast
            {
               dir = 1;
               move = true;
            }
            
            else if((key[KEY_LEFT]) &&(key[KEY_UP])) //northwest
            {
               dir = 2;
               move = true;
            }
            else if((key[KEY_RIGHT])&&(key[KEY_DOWN])) //southeast
            {
               dir = 3;
               move = true;
            }
            else if((key[KEY_LEFT])&&(key[KEY_DOWN])) //southwest
            {
               dir = 4;
               move = true;
            }
            else if(key[KEY_RIGHT]) 
            {
               dir = 5;
               move = true;
            }
            else if(key[KEY_LEFT]) 
            {
               dir = 6;
               move = true;
            }
            else if(key[KEY_UP])
            {
               dir = 7;
               move = true;
            }
            else if(key[KEY_DOWN]) 
            {
               dir = 8;
               move = true;
            
            }
            
            if(move == true)
            {
                    playerRobot.MoveObject(dir);
                    myGame.DrawPicturetoBuffer(playerRobot.GetObject(),playerRobot.GetObjectX(),playerRobot.GetObjectY());
            }
            
            if(key[KEY_SPACE])
            {
                if(fire==0)
                {
                           if( laserdir == 0)
                           {  
                               laserdir = 5;
                           } 
                           else
                           {
                               laserdir = dir;
                           }
                           laser.SetObj_X(playerRobot.GetObjectX());
                           laser.SetObj_Y(playerRobot.GetObjectY());
                           fire = 1;
                 }          
            }
            if(fire==1)
            {
                       p = laser.GetObjectX();
                       q = laser.GetObjectY();
            
                       if((p<=570)&&(p>=20)&&(q<=420)&&(q>=20))
                       {
                                  laser.MoveObject(laserdir);
                                  laser.MoveObject(laserdir);
                                  myGame.DrawPicturetoBuffer(laser.GetObject(),p,q);
                            
                            
                                  
                                  //check if our laser has hit the enemy or our goodie
                                  for(int r=0;r<=maxEnemies;r++)
                                  {  
                                        if(badRobot[r].GetAlive()==true)
                                        {
                                            isCollide = laser.IsHit(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40);
                                            if(isCollide == true)
                                            {
                                                  fire=0;
                                                  myGame.EraseFromBuffer(laser.GetObjectX(),laser.GetObjectY(), 40,20);  
                                                  myGame.EraseFromBuffer(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40); 
                                                  badRobot[r].SetAlive(false);   
                                                  
                                                  //set the blaster graphic
                                                  xplode.SetObj_X(badRobot[r].GetObjectX());
                                                  xplode.SetObj_Y(badRobot[r].GetObjectY());
                                                  enemyXplode = 0;
                                                  
                                                  //increase the score
                                                  myGame.SetScore(5);
                                            }

                                            
                                            
                                            
                                            
                                            
                                        }
                                   }
                       }
                       else
                       {
                           fire=0;
                           myGame.EraseFromBuffer(laser.GetObjectX(),laser.GetObjectY(), 40,40); 
                       }
            }   


    for(int r=0;r<=maxEnemies;r++)
    {  
        if(badRobot[r].GetAlive()==true)
        {
            //see if our robot has been hit
            isCrashed = playerRobot.IsHit(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40);
                            
            if(isCrashed == true)
            {
                        myGame.EraseFromBuffer(playerRobot.GetObjectX(),laser.GetObjectY(), 40,40);  
                        //playerRobot.SetAlive(false);   
                                                  
                       //set the blaster graphic
                       rip.SetObj_X(playerRobot.GetObjectX());
                       rip.SetObj_Y(playerRobot.GetObjectY());
                                                           
                      //increase the score
                      myGame.LoseLives();
                      showRip = 0;
            }
            }
}



            if(myGame.GetLives()<=0)
            { 
                 myGame.DrawPicturetoBuffer(gameLost.GetObject(),150,150);
                 
            }

            if(myGame.GetLevel()>=101)
            { 
                 myGame.DrawPicturetoBuffer(gameWon.GetObject(),150,150);
                 
            }

            myGame.IngameText();
            
            if(changingLevel<=100)
            {
                      myGame.DrawPicturetoBuffer(nextLevel.GetObject(),250,250);  
                      changingLevel++;          
            }
            
            
            if(enemyXplode<=10)
            {
                   enemyXplode++;          
                   myGame.DrawPicturetoBuffer(xplode.GetObject(),xplode.GetObjectX(),xplode.GetObjectY());
            }
            if(showRip<=500)
            {
                   showRip++;          
                   myGame.DrawPicturetoBuffer(rip.GetObject(),rip.GetObjectX(),rip.GetObjectY());
                  
            }
            else
            {           
                    //draw goodie robot
                    myGame.DrawPicturetoBuffer(playerRobot.GetObject(),playerRobot.GetObjectX(),playerRobot.GetObjectY());
            }
            //draw the baddy house
            myGame.DrawPicturetoBuffer(baddieHouse.GetObject(),30,300);
        
        }
        
        myGame.DrawBuffertoScreen();
    }
   
    
    myGame.CloseGame();
    return 0;  
}
END_OF_MAIN() 
