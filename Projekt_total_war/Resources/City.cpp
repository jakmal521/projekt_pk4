#include "..\Headers\City.h"
#include <stdlib.h>
//Konstruktor i destruktor
City::City( int popMax)
{
	this->populationMax = popMax;
	this->population = rand() % popMax + 1;
}

City::~City()
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
