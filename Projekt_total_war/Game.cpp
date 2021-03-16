
#include "Game.h"
//Konstruktor i destruktor
Game::Game()
{
	initWindow();
}
Game::~Game()
{
	delete this->window;
}
//funkcja uruchamiaj¹ca gre
void Game::play()
{
	while (this->window->isOpen())
	{
		this->uptade();
		this->render();
	}
}


//Funkcje inicjalizacyjne

void Game::initWindow()
{

	this->window = new RenderWindow(VideoMode(800, 600), "Total War - wersja studencka", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);

}
//Funcje do zmiany zawartoœci ekranu
void Game::uptade()
{
	Event event;
	//zamkniêcie gry przy wciscniesciu esc lub tego krzy¿yka ugóry XD
	while (this->window->pollEvent(event))
	{
		if ((event.type == Event::Closed) || (event.key.code == Keyboard::Escape))
			this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	this->window->display();
}

