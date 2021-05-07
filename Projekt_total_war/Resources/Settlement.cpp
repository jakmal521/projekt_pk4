#include "..\Headers\Settlement.h"

//Konstruktor i destruktor
Settlement::Settlement(string name, Vector2f cityPoints, Color color) :City(name, 1000, cityPoints, color)
{
	this->knightsMax = 20;
	this->archersMax = 10;
	this->horsesMax = 25;
	this->goldToUpdate = 25000;
}

Settlement::~Settlement()
{
}
