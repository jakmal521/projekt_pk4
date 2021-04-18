#include "..\Headers\CityState.h"

CityState::CityState(RenderWindow* window, stack<State*>* _states) : State(window, _states)
{
	this->initBackground(window);
	this->initFont();
	//this->initButtons();
}

CityState::~CityState()
{
}

void CityState::update()
{
	this->mousepos();
}

void CityState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
}

void CityState::end()
{
}

void CityState::initBackground(sf::RenderWindow* window)
{
	this->texture.loadFromFile("JPG/inside_city.jpg");
	this->background.setSize(Vector2f(400.f, 300.f)); //Trzeba zmieni� �eby pobiera�o wielko�� view czy co� takiego albo �eby w og�le usuwa�o view
	this->background.setTexture(&this->texture);
}

void CityState::initFont()
{
}