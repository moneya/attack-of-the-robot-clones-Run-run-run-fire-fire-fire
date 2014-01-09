#include <allegro.h>
#include <cstdlib> 
#include "objects.h"
#include "goodie.h"

Goodie::Goodie()
{
         
}

Goodie::~Goodie()
{
 } 

bool Goodie::IsHit(int objx, int objy, int widthx, int widthy)
{
     bool collision=false;
     int endy;
     int endx;
     
     endy = objy+widthy;
     endx = objx+widthx;
     
 
     if( (obj_X >= objx) && (obj_X <= endx ) && (obj_Y >= objy) && (obj_Y <= endy ))
     {
                 collision=true;                              
     }                                        
     
     return collision;
}


