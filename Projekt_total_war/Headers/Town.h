#include "..\Headers\City.h"
class Town :
    public City
{
    //Konstruktor i destruktor
public: 
    Town(std::string name, int popMax);
    ~Town();
    //Wyświetlanie i updatowanie miasta
    void update();
    void render(RenderTarget* target);

};

