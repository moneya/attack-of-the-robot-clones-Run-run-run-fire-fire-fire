class Robots: public Game
{
public:
       Robots();
       Robots(const Robots&);
       ~Robots();
       void DrawPicturetoBuffer();
       void LoadPicture(char *imgFile);
       void Setimg_X(int d);
       void Setimg_Y(int d);
       void MoveGoodie();
       
       
       BITMAP* GetBitmap() { return imgToDraw; }
       int GetX() {return img_X;}
       int GetY(){return img_Y;}
       
       
       

private:
       BITMAP *imgToDraw;
       int img_X;
       int img_Y;
        
};

