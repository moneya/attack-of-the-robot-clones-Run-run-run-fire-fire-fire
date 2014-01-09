#include <allegro.h>
#include <cstdlib> 
#include <time.h>
#include <ctime>   
#include <cstdlib> 

#include "game.h"
#include "objects.h"
#include "goodie.h"

int showLoader(int ld)
{
     ld +=1;
     return ld;
}

int randomX()
{
    int x;
    srand(x);  
    x = (rand() % 580);
    return x;
}

int randomY(int x)
{
    int y =0;
    if (x<150) //this is over the house therefore must be less than 350
    {
              srand(y);  
              y = (rand() % 280);
    }
    else 
    {
              srand(y);  
              y = (rand() % 400);  
    }
    return y;
}

int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    //create new classes
    //--------------------------------------------------------------------------
    int isrip = 0;
    bool drawKill = false;
    bool drawRip=false;
    bool move;
    bool isCollide;
    bool isCrashed;
        
    int kill = 0;
    int enemies=0;
    int maxEnemies = 100;
    int dir=0;
    int fire=0; 
    int laserdir,p,q;
    int deadRobot=0;
    int enemyXplode = 51;
    int slow = 0;
    int up=0;

    //--------------------------------------------------------------------------
    //create new classes
    //--------------------------------------------------------------------------
    Game myGame;
    myGame.SetUpGame();
        
    Goodie playerRobot;
    playerRobot.LoadObject("goodrobot.bmp");
    playerRobot.SetObj_X(100);
    playerRobot.SetObj_Y(400); 

    Goodie laser;
    laser.LoadObject("laserbeam.bmp");    
    Goodie laserup;
    laserup.LoadObject("laserbeam_up.bmp");   
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
    Objects loading;
    loading.LoadObject("loading.bmp"); 
    Objects badRobot[maxEnemies];
    
    for(int r=0;r<=maxEnemies;r++)
    {
            badRobot[r].LoadObject("badrobot.bmp");
    }
    //set the first robot  alive 
    badRobot[0].SetAlive(true);
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    myGame.InitScreen();
    
    //show loading page       
    for(int g=0; g<=500; g++)
    {
           myGame.DrawPicturetoBuffer(loading.GetObject(),150,150);
           myGame.DrawBuffertoScreen();
    }
    
    while(!key[KEY_ESC])
    {
           enemies = myGame.GetLevel()-1;
           deadRobot=0;
           myGame.DrawPicturetoBuffer(playerRobot.GetObject(),playerRobot.GetObjectX(),playerRobot.GetObjectY());
         
           //draw baddy robots
           for(int r=0;r<=enemies;r++)
           {  
                  if(badRobot[r].GetAlive()== true)
                  {
                         if(slow == 10)
                         {
                              badRobot[r].AIMove(slow);
                              slow=0;
                         }
                         else
                         {
                             slow++;
                         } 
                         myGame.DrawPicturetoBuffer(badRobot[r].GetObject(),badRobot[r].GetObjectX(),badRobot[r].GetObjectY());
                  }
                  else
                  {
                          deadRobot++;
                  }      
           }
                
           if(deadRobot>enemies) //level over
           {             
                 myGame.EraseFromBuffer(xplode.GetObjectX(),xplode.GetObjectY(), 40,40); 
                 myGame.DrawBuffertoScreen();
                 
            
                 
                 drawKill=false;
                 
                 
                 for(int g=0; g<=250; g++)
                 {
                       myGame.DrawPicturetoBuffer(nextLevel.GetObject(),125,150);
                       myGame.DrawBuffertoScreen();
                 }
                 
                 myGame.EraseFromBuffer(nextLevel.GetObjectX(),nextLevel.GetObjectY(), 401,80);  
              
                 int n = myGame.GetLevel()+1;
                 myGame.SetLevel(n);
                                                 
                 for(int r=0;r<=n;r++)
                 {
                       badRobot[r].SetAlive(true);
                       int tempStart = randomX();
                       badRobot[r].SetObj_X(tempStart);
                       badRobot[r].SetObj_Y(randomY(tempStart));
                    
                 }
                 deadRobot=0;
                 
                 playerRobot.SetObj_X(100);
                 playerRobot.SetObj_Y(400); 
           }             
                       
               

               
               //just in case our robot is dead
               if(drawRip==false)
               {
                    move = false;
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
                   }
               }
                
                           
               //------------------------------------------------------------------------------
               //have we fired? ---------------------------------------------------------------
               //------------------------------------------------------------------------------
               if(key[KEY_SPACE])
               {
                   if(laser.GetAlive()==false)
                   {
                         if( dir == 0)
                         {  
                              laserdir = 5;
                         } 
                         else
                         {
                               laserdir = dir;
                         }  
                         laser.SetObj_X(playerRobot.GetObjectX());
                         laser.SetObj_Y(playerRobot.GetObjectY());
                         laser.SetAlive(true);
                    }
               }
               //------------------------------------------------------------------------------    
               //are we still firing?----------------------------------------------------------
               //------------------------------------------------------------------------------               
               if(laser.GetAlive()==true)
               {
                      p = laser.GetObjectX();
                      q = laser.GetObjectY();
                      
                      
                 up++;
                       //is it in the bounds
                       if((p<=570)&&(p>=20)&&(q<=420)&&(q>=20)&&(up<=4))
                       {
                            laser.MoveObject(laserdir);
                            laser.MoveObject(laserdir);
                            myGame.DrawPicturetoBuffer(laser.GetObject(),p,q);
                           
                            
                       }                            
                       else if((p<=570)&&(p>=20)&&(q<=420)&&(q>=20)&&(up<=9))
                       {
                                            
                            laserup.MoveObject(laserdir);
                            laserup.MoveObject(laserdir);
                            
                            myGame.DrawPicturetoBuffer(laserup.GetObject(),p,q);
                            up=0;
                            
                            
                       }
                       else //else erease it
                       {
                            laser.SetAlive(false);
                            laserup.SetAlive(false);
                            myGame.EraseFromBuffer(laser.GetObjectX(),laser.GetObjectY(), 40,20);  
                            myGame.EraseFromBuffer(laserup.GetObjectX(),laserup.GetObjectY(), 40,20); 
                       }
                }        
                                
               //check if our laser has hit the enemy or our goodie
                for(int r=0;r<=enemies;r++)
                {  
                        if((badRobot[r].GetAlive() == true)&&(laser.GetAlive()==true))
                        {
                               isCollide = laser.IsHit(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40);
                               
                               if((isCollide == true)&&(drawKill==false))
                               {
                                        laser.SetAlive(false);
                                        myGame.EraseFromBuffer(laser.GetObjectX(),laser.GetObjectY(), 40,40);  
                        
                                        //set the blaster graphic
                                        xplode.SetObj_X(badRobot[r].GetObjectX());
                                        xplode.SetObj_Y(badRobot[r].GetObjectY());
                             
                                 
                                        myGame.EraseFromBuffer(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40); 
                                        badRobot[r].SetAlive(false); 
                                       
                                       
                                        myGame.DrawPicturetoBuffer(xplode.GetObject(),xplode.GetObjectX(),xplode.GetObjectY());                                                 
                                        //increase the score
                                        myGame.SetScore(5);
                                        drawKill=true;
                                 }
                             }
                }
                        
                  for(int r=0;r<=enemies;r++)
                  {         
                             //see if our robot has been hit
                             isCrashed = playerRobot.IsHit(badRobot[r].GetObjectX(),badRobot[r].GetObjectY(), 40,40);
                                                 
                             if((isCrashed == true)&&(drawRip==false))
                             {
                                           //set the blaster graphic
                                            rip.SetObj_X(playerRobot.GetObjectX());
                                            rip.SetObj_Y(playerRobot.GetObjectY());                                               
                                               
                                            myGame.EraseFromBuffer(playerRobot.GetObjectX(),playerRobot.GetObjectY(), 40,40);  
                                            playerRobot.SetAlive(false);   

                                             //increase the score
                                            myGame.LoseLives();
                                            myGame.DrawPicturetoBuffer(rip.GetObject(),rip.GetObjectX(),rip.GetObjectY());
                                            drawRip = true;
                              }
                                  
                }    
               
                // now draw what must always be drawn
                
                //are we still drawing bombs or rip?
                if(drawRip==true)
                {
                        isrip++;
                        myGame.DrawPicturetoBuffer(rip.GetObject(),rip.GetObjectX(),rip.GetObjectY());
                        if(isrip>250)
                        {
                                drawRip=false;
                                isrip=0;
                                myGame.EraseFromBuffer(rip.GetObjectX(),rip.GetObjectY(), 40,40); 
                                
                                playerRobot.SetObj_X(100);
                                playerRobot.SetObj_Y(400); 
                                myGame.DrawPicturetoBuffer(playerRobot.GetObject(),playerRobot.GetObjectX(),playerRobot.GetObjectY()); 
                        }  
                        

                            
                }
                                
                //are we still drawing bombs or rip?
                if(drawKill==true)
                {
                        kill++;
                        myGame.DrawPicturetoBuffer(xplode.GetObject(),xplode.GetObjectX(),xplode.GetObjectY()); 
                        if(kill>50)
                        {
                                drawKill=false;
                                kill=0;
                                myGame.EraseFromBuffer(xplode.GetObjectX(),xplode.GetObjectY(), 40,40); 
                        }         
                }

                if(myGame.GetLives()<0)
                {
                         while(!key[KEY_ESC])
                         {
                         myGame.IngameText();
                         myGame.DrawPicturetoBuffer(gameLost.GetObject(),150,100); 
                         myGame.DrawBuffertoScreen();
                         }
                         break;
                         
                }
              else if(myGame.GetLevel()>3)
                {
                         while(!key[KEY_ESC])
                         {
                         myGame.IngameText();
                         myGame.DrawPicturetoBuffer(gameWon.GetObject(),150,100); 
                         myGame.DrawBuffertoScreen();
                         }
                         break;
                         
                }

                
                myGame.IngameText();
                myGame.DrawPicturetoBuffer(baddieHouse.GetObject(),30,300);
                myGame.DrawBuffertoScreen();
    }
   
    
    myGame.CloseGame();
    return 0;  
}
END_OF_MAIN() 
