#include <sstream>
#include <map>
#include "..\Headers\GameState.h"
#include "..\Headers\Button.h"
class MainMenu :
    public State
{
public:
    //Konstruktor i  destruktor
    MainMenu(RenderWindow* window);

    virtual ~MainMenu();

private:
    //t�o
    RectangleShape background;
    Texture texture;
    //Czcionka
    Font font;
    //Przyciski
    map<string, Button*>buttons;
    void initButtons();
    void uptadeButtons();
    void renderButtons(RenderTarget* target);
    //Wy�wietlanie i uptade ekranu
    void uptade();
    void render(RenderTarget* target = nullptr);
    //Inicjacja t�a
    void initBackground();
    void initFont();
    
};

