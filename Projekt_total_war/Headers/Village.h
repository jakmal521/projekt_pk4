#include "..\Headers\City.h"
class Village :
    public City
{
public:
    //konstruktor i destruktor
    Village(int popMax);
    ~Village();
    //Wy�wietlanie i updatowanie miasta
    void update();
    void render(RenderTarget * target);
};

