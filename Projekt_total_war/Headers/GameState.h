#include <fstream>
#include <iostream>
#include <sstream>
#include "..\Headers\State.h"
#include "..\Headers\District.h"
class GameState : 
    public State
{
public:
    //Konstruktor i  destruktor
    GameState(RenderWindow* window, stack<State*>* _states);
  
    virtual ~GameState();

private: 
    //Wy�wietlanie i update ekranu
    void update();
    void render(RenderTarget* target = nullptr);
    //Wektor region�w
    map<string, District*> districts;
    //Inicjalizacja region�w
    void initDis();
    //T�o
    RectangleShape background;
    Texture texture;
    void initBackground();
};

