#include <allegro.h>
#include <cstdlib> 
#include <time.h>

#include "game.h"
#include "robots.h"

int main(int argc, char *argv[])
{
    //ALLEGRO STUFF  
    char *dir;
     
    Game myGame;
   //Laser rLaser;
    myGame.SetUpGame();
    Robots playerRobot;
    playerRobot.LoadPicture("goodrobot.bmp");
    myGame.InitScreen();
    
   
    while(!key[KEY_ESC])
    {
            if((key[KEY_RIGHT])&&(key[KEY_UP]))
            {
               playerRobot.Setimg_X(1);
               playerRobot.Setimg_Y(0);
               
            }
            else if((key[KEY_LEFT]) &&(key[KEY_UP]))
            {
               playerRobot.Setimg_X(0);
               playerRobot.Setimg_Y(0);
            }
            else if((key[KEY_RIGHT])&&(key[KEY_DOWN]))
            {
               playerRobot.Setimg_X(1);
               playerRobot.Setimg_Y(1);
            }
            else if((key[KEY_LEFT])&&(key[KEY_DOWN]))
            {
               playerRobot.Setimg_X(0);
               playerRobot.Setimg_Y(1);
            }
            else if(key[KEY_RIGHT]) 
            {
               playerRobot.Setimg_X(1);
               dir = "e";
            }
            else if(key[KEY_LEFT]) 
            {
               playerRobot.Setimg_X(0);
               dir = "w";
            }
            else if(key[KEY_UP])
            {
               playerRobot.Setimg_Y(0);
               dir = "n";
            }
            else if(key[KEY_DOWN]) 
            {
               playerRobot.Setimg_Y(1);
               dir = "w";
             
            }
            else if(key[KEY_SPACE])
            {
                 rLaser.FireLaser(dir,playerRobot.GetX(),playerRobot.GetY());
            }
            myGame.DrawPicturetoBuffer(playerRobot.GetBitmap(),playerRobot.GetX(),playerRobot.GetY());
            myGame.DrawBuffertoScreen();
    }
    
    myGame.CloseGame();
    return 0;  
}
END_OF_MAIN() 
