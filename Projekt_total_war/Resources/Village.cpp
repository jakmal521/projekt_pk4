#include "..\Headers\Village.h"
//konstruktor i destruktor

Village::Village(string name, Vector2f cityPoints, Color color) :City(name, 20000, cityPoints, color)
{
	this->knightsMax = 50;
	this->archersMax = 25;
	this->horsesMax = 70;
	this->knights = (rand() % this->knightsMax) / 4;
	this->archers = (rand() % this->horsesMax) / 4;
	this->horses = (rand() % this->archersMax) / 4;
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

int Village::getGoldToUpgrade()
{
	return this->goldToUpgradde;
}
