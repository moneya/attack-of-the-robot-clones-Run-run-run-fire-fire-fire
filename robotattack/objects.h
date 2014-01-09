class Objects
{
public:
       Objects();
       ~Objects();
       void LoadObject(char *objectFile);
       void MoveObject(int dir);
       void SetObj_X(int d);
       void SetObj_Y(int d);
              
       BITMAP* GetObject() { return objectToDraw; }
       int GetObjectX() {return obj_X;}
       int GetObjectY(){return obj_Y;}
       bool GetAlive(){return alive;}
       
       void EraseThis();
       void AIMove(int d);
       
       void SetAlive(bool isalive);
       
protected:
       int obj_X;
       int obj_Y;
       bool alive;
 private:
       BITMAP *objectToDraw;       
};

