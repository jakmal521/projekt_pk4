
#include "State.h"
class GameState :
    public State
{
public:
    //Konstruktor i  destruktor
    GameState(RenderWindow* window);
  
    virtual ~GameState();

private: 
    //Wy�wietlanie i uptade ekranu
    void uptade();
    void render(RenderTarget* target = nullptr);
};

