
#include "..\Headers\City.h"
class Settlement :
    public City
{
public:
    //Konstruktor i destruktor
    Settlement(int popMax);
    ~Settlement();
    //Wyświetlanie i updatowanie miasta
    void update();
    void render(RenderTarget* target);


};

