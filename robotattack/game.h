class Game{
      
public:
       Game();
       ~Game();
       void SetUpGame();
       void CloseGame();
       void InitScreen();
       void DrawBuffertoScreen();
       void DrawPicturetoBuffer(BITMAP *drawThis, int x, int y);
       BITMAP *buffer;
       int GetScreen_Y(){return screen_Y;}
       int GetScreen_X(){return screen_X;}

       void EraseFromBuffer(int objx, int objy, int widthx, int widthy);
       int GetLevel(){return level;}
       
       void SetLevel(int l);
       void IngameText();
       int GetLives(){return lives;}
       void LoseLives();
       int GetScore(){return score;}
       void SetScore(int s);          
       int GetStatus(){return status;}
    

       
protected:
       int screen_Y;
       int screen_X;
       int level; 
       int score;
       int lives;
       int status;

};
