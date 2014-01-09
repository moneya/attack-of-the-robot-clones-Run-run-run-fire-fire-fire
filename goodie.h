class Goodie: public Objects
{
public:
       Goodie();
       Goodie(const Goodie&);
       ~Goodie();

       bool IsHit(int objx, int objy, int widthx, int widthy);
       
        
};
