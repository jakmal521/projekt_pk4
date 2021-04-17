#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "..\Headers\City.h"
City::City()
{
}
City::City(int popMax)
{
}
//Konstruktor i destruktor
/*City::City(std::string name, int popMax)
{
	this->cityName = name;
	this->populationMax = popMax;
	this->population = rand() % popMax + 1;
}*/

City::~City()
{
}

void City::initCity(std::string name, int popMax)
{
	this->cityName = name;
	this->populationMax = popMax;
	this->population = rand() % popMax + 1;
}

void City::update()
{
}

void City::render()
{
}

//Zmiany w populacji
void City::updatePopulation()
{
	int randBorn = rand() % 100;
	int randDied = rand() % 100;
	if ((this->population -= randBorn) < 0)
		this->population = 0;
	if ((this->population -= randBorn) >= this->populationMax)
		this->population = this->populationMax;
}