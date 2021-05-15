#include "..\Headers\State.h"
//Konstruktor i destruktor
State::State(RenderWindow* window, stack<State*>*& _states)
{
	this->states = _states;
	this->window = window;
	this->ifend = false;
}

 State::~State()
{
	
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
	this->mouseposview = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}