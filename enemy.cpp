#include <stdlib.h> 
#include "enemy.h"

Enemy::Enemy()
{
          EnemyX = 220;
          EnemyY = 220;
}

Enemy::Enemy(const Enemy&)
{
     //debug            
     //textout_ex( screen, font, "IN COPY", 320, 240, makecol( 255, 0, 0), makecol( 0, 0, 0));    
}

Enemy::~Enemy()
{
 } 

void Enemy::AIMove()
{
     //upor down
     int up,right;
     up = rand() % 1 + 2;
     right = rand() % 1 + 2; 
     
     if(up==1)
     {
         EnemyX = EnemyX - (rand() % 50 + 1);     
     }
     else
     {
         EnemyX = EnemyX + (rand() % 50 + 1); 
     }
     
     if(right==1)
     {
         EnemyY = EnemyY - (rand() % 50 + 1);     
     }
     else
     {
         EnemyY = EnemyY + (rand() % 50 + 1); 
     }
   
 }
