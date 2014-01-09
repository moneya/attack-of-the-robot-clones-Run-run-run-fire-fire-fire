#include <allegro.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "robots.h"

Robots::Robots()
{
          imgToDraw = NULL;
          img_X = 0;
          img_Y = 0;
}

Robots::Robots(const Robots&)
{
     //debug            
     //textout_ex( screen, font, "IN COPY", 320, 240, makecol( 255, 0, 0), makecol( 0, 0, 0));    
}

Robots::~Robots()
{
    destroy_bitmap(imgToDraw); 
} 

void Robots::LoadPicture(char *imgFile)
{
     imgToDraw = load_bitmap(imgFile, NULL); // Load our picture
}

void Robots::Setimg_X(int d)
{
     if(d==1)
     {
             img_X++;
     }
     else
     {
             img_X--;
     }
}
void Robots::Setimg_Y(int d)
{
     if(d==1)
     {   
             img_Y++;
     }
     else
     {
             img_Y--;
     }
 }

void Robots::MoveGoodie()
{
 }
     
