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
	float aa = 0.5 * a;
	float b = 600;
	float bb = 0.5 * b;
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
	this->position.push(new Position(100.f, 2.f));
}

//Funcje do zmiany zawartoœci ekranu
void Game::update()
{
	Event event;
	//zamkniêcie gry przy wciscniesciu tego krzy¿yka u góry XD
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

	/*position.update(pos, speed);
	view.setCenter(position.GetPosition());

	position.render(*window);*/
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
		this->states.top()->render();
	this->view1.setCenter(position.top()->GetPosition());
	this->window->display();
}