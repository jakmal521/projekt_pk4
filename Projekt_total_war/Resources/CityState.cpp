#include "..\Headers\CityState.h"

CityState::CityState(RenderWindow* window, Font _font, stack<State*>* _states, City& city) : State(window, _states)
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
	this->updateInfo();
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
		if (this->city->deployUnits < 0)
		{
			this->city->deployUnits = 0;
		}
		this->ifend = true;
	}
}

void CityState::initBackground(sf::RenderWindow* window)
{
	this->texture.loadFromFile("JPG/inside_city.jpg");
	this->background.setSize(Vector2f(800.f, 600.f)); //Trzeba zmieniæ ¿eby pobiera³o wielkoœæ view czy coœ takiego albo ¿eby w ogóle usuwa³o view
	this->background.setTexture(&this->texture);
}

void CityState::initText(Font  font, City& city)
{
	stringstream ss;
	ss << "Witaj w " << city.cityName;
	this->greeting.setFont(this->font);
	this->greeting.setString(ss.str());
	cout << city.cityName << endl;
	this->greeting.setFillColor(Color::White);
	this->greeting.setCharacterSize(30);

	this->greeting.setPosition(this->window->getPosition().x - this->greeting.getGlobalBounds().width - 20, 50);
}

//inicjalizacja informacji o mieœcie
void CityState::initInfo()
{
	this->infoShape.setSize(Vector2f(150, 300));
	this->infoShape.setPosition(this->buttons.rbegin()->second->getPosX() + this->buttons.rbegin()->second->getWidth() + 50, this->buttons.rbegin()->second->getPosY());
	this->infoShape.setFillColor(Color(0, 0, 0, 150));
	this->info.setFont(this->font);

	this->info.setFillColor(Color::White);
	this->info.setCharacterSize(18);
	this->info.setPosition(this->infoShape.getPosition().x + 5, this->infoShape.getPosition().y + (this->infoShape.getGlobalBounds().height / 2) - this->info.getGlobalBounds().height / 2);
}

void CityState::updateInfo()
{
	stringstream ss;
	if (this->city->deployUnits < 0)
	{
		ss << "Nie mozna \nwyprowadzic wojska\n z pustego miasta";
		this->city->deployUnits++; //Trzeba by to zmieniæ xDDDDD
	}
	else if (this->city->deployUnits == 1)
	{
		//Dla sytuacji gdy wyprowadzamy wojsko z miasta (wpisanie 0)
		ss << "Populacja:\n" << this->city->population << "/" << this->city->populationMax << "\n"
			<< "Zapelnienie:\n" << fixed << setprecision(2) << float(this->city->population) / float(this->city->populationMax) * 100 << "% \n" << "Rycerze: 0\nKonni: " << "0\n" << "Lucznicy: " << "0";
	}
	else
	{
		ss << "Populacja:\n" << this->city->population << "/" << this->city->populationMax << "\n"
			<< "Zapelnienie:\n" << fixed << setprecision(2) << float(this->city->population) / float(this->city->populationMax) * 100 << "% \n" << "Rycerze: " << this->city->knights << "\nKonni: " << this->city->horses << "\nLucznicy: " << this->city->archers;
	}
	this->info.setString(ss.str());
}

void CityState::initButtons()
{
	if (Town* ob = dynamic_cast<Town*>(this->city))
	{
		this->buttons["Training"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25, 300, 100, &this->font, "Trenowanie wojska", Color(0, 0, 0, 150));
		this->buttons["Deploy"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.5, 300, 100, &this->font, "Wyprowadz wojsko", Color(0, 0, 0, 150));
	}
	else
	{
		stringstream ss;
		ss << "Ulepszenie miasta\n " << this->city->getGoldToUpgrade() << " zlota";
		this->buttons["Upgrade"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25, 300, 100, &this->font, ss.str(), Color(0, 0, 0, 150));
		this->buttons["Training"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.5, 300, 100, &this->font, "Trenowanie wojska", Color(0, 0, 0, 150));
		this->buttons["Deploy"] = new Button(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.75, 300, 100, &this->font, "Wyprowadz wojsko", Color(0, 0, 0, 150));
	}
}

void CityState::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mouseposview);
	if (Town* ob = dynamic_cast<Town*>(this->city))
	{
	}
	else
	{
		if (this->buttons["Upgrade"]->press())

			this->city->toUpdate = true;
	}
	if (this->buttons["Deploy"]->press())
	{
		if (this->city->deployUnits != 1 && this->city->knights == 0 && this->city->archers == 0 && this->city->horses == 0)
		{
			this->city->deployUnits = -100;
		}
		else
		{
			this->city->deployUnits = 1;
		}
	}
}

void CityState::renderButtons(RenderTarget* target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}