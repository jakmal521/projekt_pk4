#include "..\Headers\Game.h"
#include "..\Headers\Position.h"
//Konstruktor i destruktor
Game::Game()
{
	this->initWindow();
	this->initStates();
	this->initView();
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
	float a = 800;
	float b = 600;
	this->window = new RenderWindow(VideoMode(a, b), "Total War - wersja studencka", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}
void Game::initStates()
{
	this->states.push(new MainMenu(this->window, &this->states));
}
void Game::initView()
{
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(400.f, 300.f));
	this->position = new Position(100.f, 2.f);
}

//Funcje do zmiany zawartoœci ekranu
void Game::update()
{
	float dTime = 0.0f;
	sf::Clock clock;

	Event event;
	//zamkniêcie gry przy wciscniesciu tego krzy¿yka u góry XD
	while (this->window->pollEvent(event))
	{
		dTime = clock.restart().asSeconds();
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

	position->update();
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
		this->states.top()->render();
	//this->position->render(*this->window);

	//Ustawianie widoku wzglêdem poruszaj¹cego siê kwadratu
	this->view1.setCenter(position->GetPosition());
	this->window->setView(view1);
	this->window->display();
}