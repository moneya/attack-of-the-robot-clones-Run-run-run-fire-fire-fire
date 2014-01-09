class Enemy: public Objects
{
public:
       Enemy();
       Enemy(const Enemy&);
       ~Enemy();

       void AIMove();   
       
private:
        int EnemyX;
          int EnemyY;  
};
