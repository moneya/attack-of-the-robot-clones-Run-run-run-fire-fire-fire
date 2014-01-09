class Laser: public Objects
{
public:
       Laser();
       Laser(const Laser&);
       ~Laser();

       bool IsHit(int objx, int objy, int widthx, int widthy);
       
        
};
