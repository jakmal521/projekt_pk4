
#include "..\Headers\Town.h"
//konstruktor i destruktor
Town::Town(std::string name, int popMax):City(name, popMax)
{
}

Town::~Town()
{
}
//Wyœwietlanie i updatowanie miasta
void Town::update()
{
	this->updatePopulation();
}

void Town::render(RenderTarget* target)
{
}
