#pragma once
#include "..\Headers\Player.h"
class Enemy :
	public Player
{
public:
	Enemy(Color color);
	~Enemy();
	//updatowanie przeciwnik�w
	void updateEnemy();

	friend class Unit;
private:
};
