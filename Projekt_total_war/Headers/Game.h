#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <stack>
#include "..\Headers\MainMenu.h"
#include "..\Headers\Position.h"
using namespace std;
using namespace sf;
class Game
{
public:
	//Konstruktor i destruktor
	Game();
	~Game();

	void play();
private:
	//Okno g��wne
	RenderWindow* window;

	//Funckje inicjalizacyjne
	void initWindow();
	void initStates();
	void initView();
	//void initVariables();
	void updateView();

	//Funcje do zmiany zawarto�ci ekranu
	void update();
	void render();
	//Przechowywanie stan�w gry (menu, gra itp)
	stack<State*> states;

	//Przechowuje pozycje i view
	View view1;
	Position* position;
};
