
#include "..\Headers\State.h"
//Konstruktor i destruktor
State::State(RenderWindow* window)
{
	this->window = window;
	this->ifend = false;
}

State::~State()
{
	delete this->window;
}

void State::end()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->ifend = true;

	}
}

const bool State::ifending()
{
	return this->ifend;
}
//Pozycja myszki
void State::mousepos()
{
	this->mouseposscreen = Mouse::getPosition();
	this->mouseposwindow = Mouse::getPosition(*this->window);
	this->mouseposview =this->window->mapPixelToCoords( Mouse::getPosition(*this->window));
}
