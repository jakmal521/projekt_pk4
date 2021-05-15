#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Headers/Game.h"

int main()
{
	srand(time(NULL));
	Game game;
		game.play();
}
