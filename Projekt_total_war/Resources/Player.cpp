#include "..\Headers\Unit.h"
#include "..\Headers\Player.h"
//Kontruktor i destruktor
Player::Player(Color color)
{
	this->gold = 100000;
	this->color = color;
}

Player::~Player()
{
}
Color Player::playerColor()
{

	return this->color;
}
int Player::getGold()
{

	return this->gold;
}
void Player::setGold(int _gold)
{

	this->gold = _gold;

}
