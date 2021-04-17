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
	City(std::string name, int popMax);
	~City();

	void initCity(std::string name, int popMax);

	//Wy�wietlenie na ekranie
	void update();
	void render();

	//protected:
		//Tekstura
	sf::Texture cityTexture;
	//Nazwa
	std::string cityName;
	//Ilo�� ludzi
	int population;
	//ilo�� ludzi jaka maksymalnie mo�e mieszka� w mie�cie
	int populationMax;
	//zmiany w populacji
	void updatePopulation();
	//Wygl�d miasta
	Sprite sprite;
};
