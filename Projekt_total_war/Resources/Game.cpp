#include "..\Headers\Game.h"
//Konstruktor i destruktor
Game::Game()
{
	this->initWindow();
	this->initStates();
}
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
		this->states.pop();
}
//funkcja uruchamiaj¹ca gre
void Game::play()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}


//Funkcje inicjalizacyjne

void Game::initWindow()
{
	this->videoMode = VideoMode::getFullscreenModes();
	VideoMode windowsize = VideoMode::getDesktopMode();
	this->window = new RenderWindow(VideoMode(800,600), "Total War - wersja studencka", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);

}
void Game::initStates()
{
	this->states.push(new MainMenu(this->window, &this->states));
	
}
//Funcje do zmiany zawartoœci ekranu
void Game::update()
{
	Event event;
	//zamkniêcie gry przy wciscniesciu tego krzy¿yka ugóry XD
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			this->window->close();
	}

	if (!this->states.empty())
	{
		this->states.top()->update();
		if (this->states.top()->ifending())
		{
			this->states.pop();
		}
	}
	else this->window->close();
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
		this->states.top()->render();
	this->window->display();
}

