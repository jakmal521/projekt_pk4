#include "..\Headers\City.h"
class Town :
    public City
{
    //Konstruktor i destruktor
public: 
    Town(int popMax);
    ~Town();
    //Wy�wietlanie i updatowanie miasta
    void update();
    void render(RenderTarget* target);

};

