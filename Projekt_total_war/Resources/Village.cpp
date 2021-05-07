#include "..\Headers\Village.h"
//konstruktor i destruktor

Village::Village(string name, Vector2f cityPoints, Color color) :City(name, 20000, cityPoints, color)
{
	this->knightsMax = 50;
	this->archersMax = 25;
	this->horsesMax = 70;
	this->goldToUpgradde = 100000;
}

Village::Village(City* city): City(city->cityName,20000, city->cityPos,city->colorOfOwner)
{
	this->population = city->population;
	this->knightsMax = 50;
	this->archersMax = 25;
	this->horsesMax = 70;
	this->goldToUpgradde = 100000;
	this->knights = city->knights;
	this->archers = city->archers;
	this->horses = city->horses;

}

Village::~Village()
{

}
