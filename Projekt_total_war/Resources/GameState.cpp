#include "..\Headers\GameState.h"
//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states) : State(window, _states)
{
	this->initDis();
	this->initBackground();
	this->initView();
	this->initPlayer();
}

GameState::~GameState()
{
}
//Wyœwietlanie i update ekranu
void GameState::update()
{
	this->mousepos();
	this->end();
	for (auto& i : this->districts)
		i.second->update(mouseposview);
	for (auto& i : this->districts)
		this->player.back()->update(mouseposview, i.second);
	position->update();
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	for (auto& i : this->districts)
		i.second->render(this->window);
	for (auto& j : this->player)
		j->render(this->window);
	this->view1.setCenter(position->GetPosition());
	this->window->setView(view1);
}
//Inicjalizacja regionów
void GameState::initDis()
{
	string name;
	int points;
	fstream plik("Resources/districts.txt");
	while (plik >> name)
	{
		this->districts[name] = new District(name);
		plik >> points;
		this->districts[name]->shape.setPointCount(points);
		for (int i = 0; i < points; i++)
		{
			float x, y;
			plik >> x >> y;
			x = this->window->getSize().x * (x / 800);
			y = this->window->getSize().y * (y / 600);

			this->districts[name]->shape.setPoint(i, Vector2f(x, y));
		}
		//this->districts[name]->shape.scale(0.5, 0.5);
		this->districts[name]->shape.setFillColor(Color::Black);
		this->districts[name]->shape.setOutlineThickness(0);
		this->districts[name]->shape.setOutlineColor(Color::Transparent);
	}
	cout << this->districts.size();
	plik.close();
}
//Inicjacja t³a
void GameState::initBackground()
{
	this->texture.loadFromFile("JPG/sea_texture.jpg");
	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	this->background.setTexture(&this->texture);
}
//Wychodzenie z rozgrywki
void GameState::end()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->ifend = true;
	}
}

//Inicjalizacja gracza
void GameState::initPlayer()
{
	//sf::Texture = texture.loadFromFile("JPG/knight.png");
	this->player.push_back(new Player());
	this->player.back()->initPla(this->districts);

	//this->playerTexture.loadFromFile("JPG/knight.png");
	/*this->playerShape.setSize(sf::Vector2f(100.f, 100.f));
	this->playerShape.setFillColor(sf::Color::Red);
	this->player->playerShape.set*/
}

//Incjalizacja widoku
void GameState::initView()
{
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(400.f, 300.f));
	this->position = new Position();
}