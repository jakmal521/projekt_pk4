

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
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
	//Okno g³ówne
	RenderWindow* window;

	//Funckje inicjalizacyjne
	void initWindow();
	//void initVariables();

	//Funcje do zmiany zawartoœci ekranu
	void uptade();
	void render();
};

