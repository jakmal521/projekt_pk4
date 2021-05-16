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

    ~MainMenu();

private:
    //t³o
    RectangleShape background;
    Texture texture;
    //Czcionka
    Font font;
    //Przyciski
    map<string, Button*>buttons;
    void initButtons();
    void updateButtons();
    void renderButtons(RenderTarget* target);
    //Wyœwietlanie i update ekranu
    void update();
    void render(RenderTarget* target = nullptr);
    //Inicjacja t³a
    void initBackground();
    void initFont();

 
   
    
};

