
#include "..\Headers\Settlement.h"
//Konstruktor i destruktor
Settlement::Settlement(int popMax):City(popMax)
{
}

Settlement::~Settlement()
{

}
//Wyświetlanie i updatowanie miasta
void Settlement::update()
{
	this->updatePopulation();
}

void Settlement::render(RenderTarget* target)
{
}
