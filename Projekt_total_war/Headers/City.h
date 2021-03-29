#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace sf;
class City
{
public:
	//Konstruktor i destruktor
	City( int popMsax);
	~City();
	//Wy�wietlenie na ekranie
	virtual void update()=0;
	virtual void render()=0;
protected:
	//Ilo�� ludzi
	int population;
	//ilo�� ludzi jaka maksymalnie mo�e mieszka� w mie�cie
	int populationMax;
	//zmiany w populacji
	void updatePopulation();
	//Wygl�d miasta 
	Sprite sprite;

};

