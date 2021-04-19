#include <sstream>
#include <map>
#include "..\Headers\GameState.h"
#include "..\Headers\Button.h"

class MainMenu :
    public State
{
public:
    //Konstruktor i  destruktor
    MainMenu(RenderWindow* window, stack<State*>* _states);

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
    void updateButtons();
    void renderButtons(RenderTarget* target);
    //Wy�wietlanie i update ekranu
    void update();
    void render(RenderTarget* target = nullptr);
    //Inicjacja t�a
    void initBackground();
    void initFont();
    //
    void end();
    
};

