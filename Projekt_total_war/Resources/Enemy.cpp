#pragma once
#include "..\Headers\Enemy.h"

Enemy::Enemy(Color color) : Player(color)
{
}

Enemy::~Enemy()
{
}

//updatowanie przeciwników
void Enemy::updateEnemy(map<string, District*> districts)
{
	int sum = 0;
	for (auto& i : districts)
	{
		if (i.second->cities.back()->colorOfOwner == this->playerColor())
			sum += i.second->cities.back()->population / 10;
	}
	this->setGold(this->getGold() + sum);
}