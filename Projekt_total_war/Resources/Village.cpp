#include "..\Headers\Village.h"
//konstruktor i destruktor


Village::Village(int popMax):City(popMax)
{
}

Village::~Village()
{
}
//Wyœwietlanie i updatowanie miasta
void Village::update()
{
	this->updatePopulation();

}
