#include "..\Headers\Village.h"
//konstruktor i destruktor


Village::Village(int popMax):City(popMax)
{
}

Village::~Village()
{
}
//Wy�wietlanie i updatowanie miasta
void Village::update()
{
	this->updatePopulation();

}
