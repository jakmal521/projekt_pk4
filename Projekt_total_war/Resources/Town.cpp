
#include "..\Headers\Town.h"
//konstruktor i destruktor
Town::Town(string name, Vector2f cityPoints, Color color):City(name, 80000, cityPoints, color)
{
	this->knightsMax = 80;
	this->archersMax = 40;
	this->horsesMax = 100;
	this->knights =(rand()%this->knightsMax) /4;
	this->archers = (rand() % this->horsesMax) / 4;
	this->horses = (rand() % this->archersMax) / 4;
}

Town::Town(City* city) :City(city->cityName, 20000, city->cityPos, city->colorOfOwner)
{
	this->population = city->population;
	this->knightsMax = 80;
	this->archersMax = 40;
	this->horsesMax = 100;
	this->knights = city->knights;
	this->archers = city->archers;
	this->horses = city->horses;
}

Town::~Town()
{

}



