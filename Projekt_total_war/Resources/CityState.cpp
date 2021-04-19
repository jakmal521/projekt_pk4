#include "..\Headers\CityState.h"

CityState::CityState(RenderWindow* window,Font _font, stack<State*>* _states, City &city) : State(window, _states)
{	
	this->initBackground(window);
	//this->initButtons();
	this->font = _font;
	this->initText(font, city);

	
}

CityState::~CityState()
{
}

void CityState::update()
{
	this->mousepos();
	this->end();
}

void CityState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->cityName);
}

void CityState::end()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->ifend = true;
	}
}

void CityState::initBackground(sf::RenderWindow* window)
{
	this->texture.loadFromFile("JPG/inside_city.jpg");
	this->background.setSize(Vector2f(800.f, 600.f)); //Trzeba zmieniæ ¿eby pobiera³o wielkoœæ view czy coœ takiego albo ¿eby w ogóle usuwa³o view
	this->background.setTexture(&this->texture);
}

void CityState::initText(Font  font, City & city)
{
	
	this->cityName.setFont(this->font);
	this->cityName.setString(city.cityName);
	cout << city.cityName << endl;
	this->cityName.setFillColor(Color::Red);
	this->cityName.setCharacterSize(40);
	this->cityName.setPosition(681,158);
	
}
void CityState::initButtons()
{

}
