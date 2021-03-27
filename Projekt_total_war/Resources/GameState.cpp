#include "..\Headers\GameState.h"
//Konstruktory i destruktory
GameState::GameState(RenderWindow* window,stack<State*>* _states): State(window, _states)
{

	this->initDis();
	this->initBackground();
}

GameState::~GameState()
{

}
//Wy�wietlanie i update ekranu
void GameState::update()
{
	this->mousepos();
	this->end();
	for (auto& i : this->districts)
		i.second->update(mouseposview);
}

void GameState::render(RenderTarget* target )
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	for (auto& i : this->districts)
		i.second->render(this->window);
}
//Inicjalizacja region�w
void GameState::initDis()
{
	string name;
	int points;
	fstream plik("Resources/districts.txt");
	while (plik >> name)
	{
		this->districts[name]=new District(name);
		plik >> points;
		this->districts[name]->shape.setPointCount(points);
		for (int i = 0; i < points; i++)
		{
			float x, y;
			plik >> x >> y;
			this->districts[name]->shape.setPoint(i, Vector2f(x,y));

		}

		this->districts[name]->shape.setFillColor(Color::Blue);
		this->districts[name]->shape.setOutlineThickness(2);
		this->districts[name]->shape.setOutlineColor(Color(0,0,0,0));
	}
	cout << this->districts.size();
	plik.close();

}
//Inicjacja t�a
void GameState::initBackground()
{
	
	this->texture.loadFromFile("JPG/sea_texture.jpg");
	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	this->background.setTexture(&this->texture);
}
