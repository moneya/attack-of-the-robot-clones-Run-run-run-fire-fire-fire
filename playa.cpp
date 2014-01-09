#include <allegro.h>
#include <cstdlib> 
#include "objects.h"
#include "playa.h"

Playa::Playa()
{
      lives = 5;   
}

Playa::~Playa()
{
}    

void Playa::SetLives(int v)
{
     lives = v;
}

bool Playa::IsCrash(int objx, int objy, int widthx, int widthy)
{
     bool crash=false;
     int endy;
     int endx;
     
     endy = objy+widthy;
     endx = objx+widthx;
     
 
     if( (obj_X >= objx) && (obj_X <= endx ) && (obj_Y >= objy) && (obj_Y <= endy ))
     {
                 crash=true;                              
     }                                        
     
     return crash;
}

