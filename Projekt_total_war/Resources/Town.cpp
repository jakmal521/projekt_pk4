
#include "..\Headers\Town.h"
//konstruktor i destruktor
Town::Town(int popMax):City(popMax)
{
}

Town::~Town()
{
}
//Wy�wietlanie i updatowanie miasta
void Town::update()
{
	this->updatePopulation();
}

void Town::render(RenderTarget* target)
{
}
