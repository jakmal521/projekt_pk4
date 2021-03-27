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
    //Wyœwietlanie i update ekranu
    void update();
    void render(RenderTarget* target = nullptr);
    //Wektor regionów
    map<string, District*> districts;
    //Inicjalizacja regionów
    void initDis();
    //T³o
    RectangleShape background;
    Texture texture;
    void initBackground();
};

