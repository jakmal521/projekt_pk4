#pragma once
#include "..\Headers\Player.h"
#include "..\Headers\\District.h"
class Enemy :
	public Player
{
public:
	Enemy(Color color);
	~Enemy();
	//updatowanie przeciwników
	void updateEnemy(map<string, District*> districts);

	friend class Unit;

};
