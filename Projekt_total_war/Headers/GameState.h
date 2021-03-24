
#include "State.h"
class GameState :
    public State
{
public:
    //Konstruktor i  destruktor
    GameState(RenderWindow* window);
  
    virtual ~GameState();

private: 
    //Wyświetlanie i uptade ekranu
    void uptade();
    void render(RenderTarget* target = nullptr);
};

