#include <allegro.h>
#include <time.h>
#include <stdlib.h>

#include "objects.h"
#include "game.h"

Objects::Objects()
{
          objectToDraw = NULL;
          obj_X = 50;
          obj_Y = 50;
          alive = false;
}

Objects::~Objects()
{
    destroy_bitmap(objectToDraw); 
} 

void Objects::LoadObject(char *objFile)
{
     objectToDraw = load_bitmap(objFile, NULL); // Load our picture
}

void Objects::SetObj_X(int d)
{
     obj_X = d;
}
void Objects::SetObj_Y(int d)
{
    obj_Y = d;
}



void Objects::MoveObject(int dir)
{
    if(dir==1) //northeast
     {
               obj_X++;
               obj_Y--;     
     }
     else if(dir==2) //northwest
     {
               obj_X--;
               obj_Y--; 
     }
     else if(dir==3) //southeast
     {
               obj_X++;
               obj_Y++;               
     }
     else if(dir==4) //southwest
     {
               obj_X--;
               obj_Y++;               
     }
     else if(dir==6) //north
     {
              obj_X--; 
     }
     else if(dir==5) //south
     {
              obj_X++; 
     }
     else if(dir==8) //east
     {
              obj_Y++;
     }
     else if(dir==7) //west
     {
              obj_Y--;
     }  
     
     if(obj_X>=590)
     {
        obj_X=590;           
     }
     if(obj_X<=10)
     {
        obj_X=10;           
     }
     if(obj_Y>=430)
     {
        obj_Y=430;           
     }
     if(obj_Y<=10)
     {
        obj_Y=10;           
     }               
}


void Objects::AIMove(int g)
{
     //upor down
     int up,right;
     
    
         up = rand() % 10 + 1;
         right = rand() % 10 + 1; 
         
         if(up==1)//up
         {
            obj_X=obj_X+10;
            obj_Y=obj_Y+10;        
             MoveObject(6);       
         }
         if(up==5)//down
         {
            obj_X=obj_X+10;
            obj_Y=obj_Y-10; 
            MoveObject(5);       
         }
         
         if(right==7)//rite
         {
            obj_X=obj_X-10;
            obj_Y=obj_Y+10;   
            MoveObject(8);      
         }
         if(right==3)//left
         {  
            obj_X=obj_X-10;
            obj_Y=obj_Y-10;
            MoveObject(7);  
         }
     
 }
 
 void Objects::SetAlive(bool isalive)
 {
      alive = isalive;
      }
