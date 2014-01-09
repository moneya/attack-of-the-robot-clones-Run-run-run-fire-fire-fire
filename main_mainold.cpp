#include <allegro.h>
#include <cstdlib> 
#include <time.h>

#include "game.h"
#include "objects.h"
#include "goodie.h"

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

    Objects gameLoading;
    gameLoading.LoadObject("loading.bmp"); 

    Objects gameWon;
    gameWon.LoadObject("gameoverwon.bmp");     
    
    Objects badRobot[maxEnemies];
    
    for(int r=0;r<=maxEnemies;r++)
    {
            badRobot[r].LoadObject("badrobot.bmp");
    }


int LoadingCounter(int lc)
{
    lc += 1;
    return lc;
}

int MovePlayer(void)
{
     int dir;
         if((key[KEY_RIGHT])&&(key[KEY_UP])) //northeast
         {
               dir = 1;
         }
         else if((key[KEY_LEFT]) &&(key[KEY_UP])) //northwest
         {
               dir = 2;
         }
         else if((key[KEY_RIGHT])&&(key[KEY_DOWN])) //southeast
         {
               dir = 3;
         }
         else if((key[KEY_LEFT])&&(key[KEY_DOWN])) //southwest
         {
               dir = 4;
         }
         else if(key[KEY_RIGHT]) 
         {
               dir = 5;
         }
         else if(key[KEY_LEFT]) 
         {
               dir = 6;
         }
         else if(key[KEY_UP])
         {
              dir = 7;
         }
         else if(key[KEY_DOWN]) 
         {
              dir = 8;
         }
     return dir; 
}

bool AllRobotsKilled(int a,int b)
{
    // a is the level
    // b is the number of robots killed
     bool allDead;
     
     if(a<=b) //the level is less than the number of robots killed
     {
         allDead = true; 
     }    
     else
     {
         allDead = false;
     }
     
     return allDead; 
}

int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    //create new classes
    //--------------------------------------------------------------------------
    int currentstatus;
    int dir = 5;
    int loader = 0;
    bool endLevel = false;
    int currentLevel = 1;
    int currentLives;
    bool fire = false;
    
    

    int laserdir,p,q;
    int count=0;
    
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
    //--------------------------------------------------------------------------
    
    
    maxEnemies = myGame.GetLevel();
    myGame.InitScreen();
       
    while(!key[KEY_ESC])
    {
            deadRobot=0;
            //draw baddy robots
            

            currentLives = myGame.GetLives();
            currentLevel = myGame.GetLevel();
            //now lets see if we are changing levels?
            endlevel = AllRobotsKilled(currentLevel,deadRobot); 


            
            //lets see if the status is loading
            if(loader<=1000)
            {
                 loader = LoadingCounter(loader);
                 myGame.SetStatus(1);      
            }
           
            //the level is ended and the current level is less than the max
            if(endlevel == true)
            {
                  myGame.SetStatus(7);        
            }

            //the level is ended and the current level is less than the max
            if(currentLevel<=maxEnemies)
            {
                  myGame.SetStatus(4);        
            }
           
            //have we run out of lives
            if(currentLives<0)
            {
                  myGame.SetStatus(5);        
            }

          
            
            //get the status before we switch it
            currentstatus = myGame.GetStatus();
            
            
            switch (currentstatus)
            {
                   //-----------------------------------------------case 1-loading--
                   case 1:
                        myGame.DrawPicturetoBuffer(gameLoading.GetObject(),150,150);
                        break;
                   //-----------------------------------------------case 2-Play--
                   case 2:   
                        dir = MovePlayer();
                        move = true;
                        playerRobot.MoveObject(dir);
                        myGame.DrawPicturetoBuffer(playerRobot.GetObject(),playerRobot.GetObjectX(),playerRobot.GetObjectY());
                        break;  
                   //-----------------------------------------------case 3-Lost--
                   case 3:                         
                        myGame.DrawPicturetoBuffer(gameLost.GetObject(),150,150);
                        break;
                   //-----------------------------------------------case 4-Won--     
                   case 4:
                        myGame.DrawPicturetoBuffer(gameWon.GetObject(),150,150);
                        break;
                   //-----------------------------------------------case 5-goodie killed--     
                   case 5:
                        myGame.DrawPicturetoBuffer(rip.GetObject(),rip.GetObjectX(),rip.GetObjectY());
                        break;
                   //-----------------------------------------------case 6-baddie killed--     
                   case 6:
                        myGame.DrawPicturetoBuffer(xplode.GetObject(),xplode.GetObjectX(),xplode.GetObjectY());
                        break;
                   //-----------------------------------------------case 7-changing level--     
                   case 7:   
                        myGame.DrawPicturetoBuffer(nextLevel.GetObject(),250,250);  
                        break;
                   //-----------------------------------------------case 7-fire laser--     
                   case 8:  
                        myGame.DrawPicturetoBuffer(laser.GetObject(),p,q);
                        break;                        
                                                                
            }
           
            //have we fired our rocket??
            if(key[KEY_SPACE])
            {
                  myGame.SetStatus(8);
                  //set the x and y of this laser
                  fire=true;
                  //use the dir
                  
                            
            }  
           
           
           
           
           
           
           
           
           
           
            //this is what has to be drawn everytime
            myGame.IngameText();
            myGame.DrawPicturetoBuffer(baddieHouse.GetObject(),30,300);
            
            
            //AllRobotsKilled(int a,int b)
           for(int r=0;r<=maxEnemies;r++)
           {  
              if(badRobot[r].GetAlive()== false)
              {
                   //we have a dead robot so lets increment the value                       
                   deadRobot++;
                   
                   if(deadRobot==maxEnemies)
                   {
                           myGame.SetStatus(7);       
                           int oldlevel = myGame.GetLevel();
                           int newlevel = oldlevel+1;
                           myGame.SetLevel(newlevel);
                           maxEnemies = newlevel;
                             
    
                           for(int r=0;r<=maxEnemies;r++)
                           {
                                   badRobot[r].SetAlive(true);
                           }
                    }
                }  
            }      
                       
           //for normal play             
           for(int r=0;r<=maxEnemies;r++)
           {
                   //random move
                   badRobot[r].AIMove(0);
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




            
        
        }
        
        myGame.DrawBuffertoScreen();
    }
   
    
    myGame.CloseGame();
    return 0;  
}
END_OF_MAIN() 
