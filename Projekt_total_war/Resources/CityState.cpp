#include "..\Headers\CityState.h"

CityState::CityState(RenderWindow* window,Font _font, stack<State*>* _states, City &city) : State(window, _states)
{	
	this->initBackground(window);
	this->city = &city;
	this->font = _font;
	this->initText(font, city);
	this->initButtons();
	this->initInfo();
}

CityState::~CityState()
{
}

void CityState::update()
{
	this->mousepos();
	this->end();
	this->updateButtons();
}

void CityState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->greeting);
	this->renderButtons(this->window);
	target->draw(this->infoShape);
	target->draw(this->info);
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
	stringstream ss;
	ss << "Witaj w " << city.cityName;
	this->greeting.setFont(this->font);
	this->greeting.setString(ss.str());
	cout << city.cityName << endl;
	this->greeting.setFillColor(Color::White);
	this->greeting.setCharacterSize(30);
		  
	this->greeting.setPosition(this->window->getPosition().x -  this->greeting.getGlobalBounds().width-20, 50);

}
//inicjalizacja informacji o mieœcie
void CityState::initInfo()
{
	this->infoShape.setSize(Vector2f(150, 300));
	this->infoShape.setPosition(this->buttons["Upgrade"]->getPosX() + this->buttons["Upgrade"]->getWidth() + 50, this->buttons["Upgrade"]->getPosY());
	this->infoShape.setFillColor(Color(0, 0, 0, 150));
	this->info.setFont(this->font);
	
	this->info.setFillColor(Color::White);
	this->info.setCharacterSize(18);
	this->info.setPosition(this->infoShape.getPosition().x +5, this->infoShape.getPosition().y + (this->infoShape.getGlobalBounds().height / 2) - this->info.getGlobalBounds().height / 2);
	stringstream ss;

	ss << "Populacja:\n" << this->city->population << "/" << this->city->populationMax << "\n"
		<< "Zapelnienie:\n" << fixed << setprecision(2) << float(this->city->population) / float(this->city->populationMax) * 100 << "% ";
	this->info.setString(ss.str());
}
void CityState::initButtons()
{
	this->buttons["Upgrade"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25, 300, 100, &this->font, "Ulepszenie miasta", Color(0, 0, 0, 150));
	this->buttons["Training"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.5, 300, 100, &this->font, "Trenowanie wojska", Color(0, 0, 0, 150));
	this->buttons["Buildings"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.75, 300, 100, &this->font, "Budynki", Color(0, 0, 0, 150));
	
}
void CityState::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mouseposview);
}

void CityState::renderButtons(RenderTarget* target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}