#pragma once
#include "..\Headers\Player.h"
class Enemy :
    public Player
{
public:
   Enemy(Color color);
   ~Enemy();
   //updatowanie przeciwników
   void update();
private:
};

