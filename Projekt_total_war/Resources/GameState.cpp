#include "..\Headers\GameState.h"
//Konstruktory i destruktory
GameState::GameState(RenderWindow* window): State(window)
{
}

GameState::~GameState()
{

}
//Wyœwietlanie i uptade ekranu
void GameState::uptade()
{
	this->mousepos();
	this->end();
}

void GameState::render(RenderTarget* target )
{
	if (!target)
		target = this->window;
}
