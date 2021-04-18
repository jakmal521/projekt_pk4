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
class City
{
public:
	//Konstruktor i destruktor
	City();
	City(std::string name, int popMax, sf::Vector2f cityPoints);
	~City();

	//Wyœwietlenie na ekranie
	void update(Vector2f mposC);
	void render(RenderTarget* target);

	//Inicjowanie miasta
	void initCity(sf::Vector2f cityPos);

protected:

	/*Mechanika*/
	//Zegar potrzebny do sprawdzenia czy by³ double click
	sf::Clock clickClock;
	//Czy mysz jest przytrzymywana
	bool mouseHeld;
	//Po³o¿enie
	sf::Vector2f cityPos;

	/*Wygl¹d*/
	//Tekstury
	sf::Texture cityIconTexture;
	sf::Color cityIconColor;
	sf::Texture insideCityTexture;
	//Wygl¹d miasta
	RectangleShape cityIcon;
	Sprite sprite;

	/*Wartoœci w grze*/
	//Nazwa
	std::string cityName;
	//Iloœæ ludzi
	int population;
	//iloœæ ludzi jaka maksymalnie mo¿e mieszkaæ w mieœcie
	int populationMax;
	//zmiany w populacji
	void updatePopulation();
};
