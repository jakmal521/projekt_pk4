#include "..\Headers\Unit.h"
#include "..\Headers\Player.h"
//Kontruktor i destruktor
Player::Player(Color color)
{
	this->gold = 0;
	this->color = color;
}

Player::~Player()
{
}
Color Player::playerColor()
{

	return this->color;
}
