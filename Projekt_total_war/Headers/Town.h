#include "..\Headers\City.h"
class Town :
    public City
{
    //Konstruktor i destruktor
public: 
    Town(int popMax);
    ~Town();
    //Wyœwietlanie i updatowanie miasta
    void update();
    void render(RenderTarget* target);

};

