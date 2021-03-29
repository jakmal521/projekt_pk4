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
	//Wyœwietlenie na ekranie
	virtual void update()=0;
	virtual void render()=0;
protected:
	//Iloœæ ludzi
	int population;
	//iloœæ ludzi jaka maksymalnie mo¿e mieszkaæ w mieœcie
	int populationMax;
	//zmiany w populacji
	void updatePopulation();
	//Wygl¹d miasta 
	Sprite sprite;

};

