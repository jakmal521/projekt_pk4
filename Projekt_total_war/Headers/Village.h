#include "..\Headers\City.h"
class Village :
    public City
{
public:
    //konstruktor i destruktor
    Village(std::string name, int popMax);
    ~Village();
    //Wyświetlanie i updatowanie miasta
    void update();
    void render(RenderTarget * target);
};

