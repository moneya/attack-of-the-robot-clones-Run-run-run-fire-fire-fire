class Playa: public Objects
{
public:
       Playa();
       Playa(const Playa&);
       ~Playa();
       
       int Getlives(){return lives;}       
       void SetLives(int v);
       bool IsCrash(int objx, int objy, int widthx, int widthy);

private:
        int lives;
       
        
};
