#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;
class City
{
public:
	//Konstruktor i destruktor
	City();
	City(std::string name, int popMax, sf::Vector2f cityPoints);
	~City();

	//Wy�wietlenie na ekranie
	void update(Vector2f mposC);
	void render(RenderTarget* target);

	//Inicjowanie miasta
	void initCity(sf::Vector2f cityPos);

	//Zwracanie czy wej�� do miasta
	bool isInCity();
	//
	void setNotInCity();
	//Akcesory
	/*string CityName();
	int Population();
	int PopulationMax();
	*/
protected:

	/*Mechanika*/
	//Zegar potrzebny do sprawdzenia czy by� double click
	sf::Clock clickClock;
	//Czy mysz jest przytrzymywana
	bool mouseHeld;
	//Po�o�enie
	sf::Vector2f cityPos;
	//Czy wej�� do miasta
	bool doubleClicked;

	/*Wygl�d*/
	//Tekstury
	sf::Texture cityIconTexture;
	sf::Color cityIconColor;
	sf::Texture insideCityTexture;
	//Wygl�d miasta
	RectangleShape cityIcon;
	Sprite sprite;

	/*Warto�ci w grze*/
	//Nazwa
	std::string cityName;
	//Ilo�� ludzi
	int population;
	//ilo�� ludzi jaka maksymalnie mo�e mieszka� w mie�cie
	int populationMax;
	//zmiany w populacji
	void updatePopulation();
	friend class CityState;
};
