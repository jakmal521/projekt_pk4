#include "..\Headers\CityState.h"

CityState::CityState(RenderWindow* window, Font _font, stack<State*>* _states, City& city, int gold, Player* player) : State(window, _states)
{
	this->mouseHeld = false;
	this->initBackground(window);
	this->city = &city;
	this->font = _font;
	this->initText(font, city);
	this->initButtons();
	this->initInfo();
	this->ownerGold = player->getGold();
	this->timeToSeeAlert = -1;
	this->hiddenMainbuttons = false;
	this->newArcher = 0;
	this->newHorse = 0;
	this->newKnight = 0;
	this->player = player;

}

CityState::~CityState()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}
	
	this->player->setGold(this->ownerGold);
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
	if (!this->timeToSeeAlert)
	{
		this->timeToSeeAlert = -1;
		this->error.setString("");
	}
	else if (this->timeToSeeAlert > 0)
	{
		this->error.setPosition(0, 0);
		this->timeToSeeAlert--;
		target->draw(this->error);
	}
	target->draw(this->newKnightsText);
	target->draw(this->newHorsesText);
	target->draw(this->newArchersText);
	target->draw(this->knightsText);
	target->draw(this->horsesText);
	target->draw(this->archersText);
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
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setTexture(&this->texture);
}

void CityState::initText(Font  font, City& city)
{
	stringstream ss;
	ss << "Witaj w " << city.cityName;
	this->greeting.setFont(this->font);
	this->greeting.setString(ss.str());
	this->greeting.setFillColor(Color::White);
	this->greeting.setCharacterSize(30);
	this->greeting.setPosition(this->window->getPosition().x, 50);

	this->error.setFont(this->font);
	this->error.setString("");
	this->error.setFillColor(Color::Red);
	this->error.setCharacterSize(20);

	this->newKnightsText.setFont(this->font);
	this->newKnightsText.setString("0");
	this->newKnightsText.setFillColor(Color::White);
	this->newKnightsText.setCharacterSize(20);
	this->newKnightsText.setPosition(-100, this->window->getSize().y * 0.25);

	this->newHorsesText.setFont(this->font);
	this->newHorsesText.setString("0");
	this->newHorsesText.setFillColor(Color::White);
	this->newHorsesText.setCharacterSize(20);
	this->newHorsesText.setPosition(-100, this->window->getSize().y * 0.50);

	this->newArchersText.setFont(this->font);
	this->newArchersText.setString("0");
	this->newArchersText.setFillColor(Color::White);
	this->newArchersText.setCharacterSize(20);
	this->newArchersText.setPosition(-100, this->window->getSize().y * 0.75);

	this->knightsText.setFont(this->font);
	this->knightsText.setString("Nowi rycerze");
	this->knightsText.setFillColor(Color::Red);
	this->knightsText.setCharacterSize(30);
	this->knightsText.setPosition(-300, this->window->getSize().y * 0.75);

	this->horsesText.setFont(this->font);
	this->horsesText.setString("Nowi konni");
	this->horsesText.setFillColor(Color::Red);
	this->horsesText.setCharacterSize(30);
	this->horsesText.setPosition(-300, this->window->getSize().y * 0.50);

	this->archersText.setFont(this->font);
	this->archersText.setString("Nowi lucznicy");
	this->archersText.setFillColor(Color::Red);
	this->archersText.setCharacterSize(30);
	this->archersText.setPosition(-300, this->window->getSize().y * 0.75);

}

//inicjalizacja informacji o mieœcie
void CityState::initInfo()
{
	this->infoShape.setSize(Vector2f(300, 300));
	if (Town* ob = dynamic_cast<Town*>(this->city))
	{
		this->infoShape.setPosition(this->buttons["Training"]->getPosX() + this->buttons["Training"]->getWidth() + 50, this->buttons["Training"]->getPosY() + this->buttons["Training"]->getHeight() / 2);
	}
	else
	{
		this->infoShape.setPosition(this->buttons["Upgrade"]->getPosX() + this->buttons["Upgrade"]->getWidth() + 50, this->buttons["Upgrade"]->getPosY() + this->buttons["Upgrade"]->getHeight() / 2);
	}
	this->infoShape.setFillColor(Color(0, 0, 0, 150));
	this->info.setFont(this->font);

	this->info.setFillColor(Color::White);
	this->info.setCharacterSize(18);
}

void CityState::updateInfo()
{
	stringstream ss;
	if (this->city->deployUnits == 1)
	{
		this->error.setString("Wojsko wyszlo z miasta!");

		ss << "Populacja:\n" << this->city->population << "/" << this->city->populationMax << "\n"
			<< "Zapelnienie:\n" << fixed << setprecision(2) << float(this->city->population) / float(this->city->populationMax) * 100 << "% \n" << "Rycerze: " << 0 << "\nKonni: " << 0 << "\nLucznicy: " << 0;
	}
	else
	{
		ss << "Populacja:\n" << this->city->population << "/" << this->city->populationMax << "\n"
			<< "Zapelnienie:\n" << fixed << setprecision(2) << float(this->city->population) / float(this->city->populationMax) * 100 << "% \n" << "Rycerze: " << this->city->knights << "\nKonni: " << this->city->horses << "\nLucznicy: " << this->city->archers;
	}
	this->info.setString(ss.str()); this->info.setPosition(this->infoShape.getPosition().x + (this->infoShape.getGlobalBounds().width / 2) - this->info.getGlobalBounds().width / 2, this->infoShape.getPosition().y + (this->infoShape.getGlobalBounds().height / 2) - this->info.getGlobalBounds().height / 2);
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
	this->buttons["submit"] = new Button(-300, this->window->getSize().y * 0.75, 300, 100, &this->font, "Trenuj", Color(0, 0, 0, 150));
	this->buttons["+knights"] = new Button(-100, this->window->getSize().y * 0.25, 50, 50, &this->font, "+", Color(0, 0, 0, 150));
	this->buttons["+horses"] = new Button(-100, this->window->getSize().y * 0.5, 50, 50, &this->font, "+", Color(0, 0, 0, 150));
	this->buttons["+archers"] = new Button(-100, this->window->getSize().y * 0.75, 50, 50, &this->font, "+", Color(0, 0, 0, 150));
	this->buttons["-knights"] = new Button(-100, this->window->getSize().y * 0.25, 50, 50, &this->font, "-", Color(0, 0, 0, 150));
	this->buttons["-horses"] = new Button(-100, this->window->getSize().y * 0.5, 50, 50, &this->font, "-", Color(0, 0, 0, 150));
	this->buttons["-archers"] = new Button(-100, this->window->getSize().y * 0.75, 50, 50, &this->font, "-", Color(0, 0, 0, 150));
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
		if (this->city->toUpdate && this->buttons["Upgrade"]->press())
		{
			this->timeToSeeAlert = 100;
			this->error.setString("Wyjdz z miasta a zobaczysz efekty przy najblizszej wizycie!");
			
			
		}
		else if (this->buttons["Upgrade"]->press() && this->ownerGold >= this->city->getGoldToUpgrade() && !this->city->toUpdate)
		{
			this->city->toUpdate = true;
			this->ownerGold -= this->city->getGoldToUpgrade();
		}
		else if (this->buttons["Upgrade"]->press() && this->ownerGold < this->city->getGoldToUpgrade())
		{
			this->timeToSeeAlert = 100;
			this->error.setString("Brak odpowiedniej ilosci zlota!");
		}
	}
	if (this->buttons["Deploy"]->press())
	{
		if (this->city->deployUnits != 1 && this->city->knights == 0 && this->city->archers == 0 && this->city->horses == 0)
		{
			this->timeToSeeAlert = 100;
			this->error.setString("Nie mozna wyprowadzic nie istniejacych jednostek");
		}
		else if (this->city->deployUnits == 1)
		{
			this->timeToSeeAlert = 100;
			this->error.setString("Jednostki wyprowadzone");
		}
		else
		{
			this->city->deployUnits = 1;
		}
	}
	if (this->buttons["Training"]->press())
	{
		this->hidingMainButtons();
		this->hiddenMainbuttons = true;
	}

	if (this->hiddenMainbuttons)
	{
		int sum = 0;
		if (this->buttons["+archers"]->press())
		{
			if (this->city->archers + this->newArcher != this->city->archersMax)
			{
				this->newArcher++;
			}
			else
			{
				this->timeToSeeAlert = 100;
				this->error.setString("Nie mozna wytrenowac wiecej lucznikow!");
			}
		}
		else if (this->buttons["-archers"]->press())
		{
			if (this->newArcher)
				this->newArcher--;
		}

		if (this->buttons["+horses"]->press())
		{
			if (this->city->horses + this->newHorse != this->city->horsesMax)
			{
				this->newHorse++;
			}
			else
			{
				this->timeToSeeAlert = 100;
				this->error.setString("Nie mozna wytrenowac wiecej konnych!");
			}
		}
		else if (this->buttons["-horses"]->press())
		{
			if (this->newHorse)
				this->newHorse--;
		}
		if (this->buttons["+knights"]->press())
		{
			if (this->city->knights + this->newKnight != this->city->knightsMax)
			{
				this->newKnight++;
			}
			else
			{
				this->timeToSeeAlert = 100;
				this->error.setString("Nie mozna wytrenowac wiecej rycerzy!");
			}
		}
		else if (this->buttons["-knights"]->press())
		{
			if (this->newKnight)
				this->newKnight--;
		}

		this->newArchersText.setString(to_string(newArcher));
		this->newHorsesText.setString(to_string(newHorse));
		this->newKnightsText.setString(to_string(newKnight));
		stringstream ss;
		sum = (newKnight * 400 + newHorse * 500 + newArcher * 300);
		ss << "Trenuj\n" << (newKnight * 400 + newHorse * 500 + newArcher * 300) << " zlota";
		this->buttons["submit"]->text.setString(ss.str());

		if (this->buttons["submit"]->press() && this->ownerGold >= sum)
		{
			this->hiddenMainbuttons = false;
			this->ownerGold -= sum;
			this->city->archers += this->newArcher;
			this->city->knights += this->newKnight;
			this->city->horses += this->newHorse;
			if (this->city->isUnitsDeployed())
				this->city->deployUnits = false;
			this->updateInfo();
			this->showingMainButtons();
		}
		else if (this->buttons["submit"]->press() && this->ownerGold < sum)
		{
			this->timeToSeeAlert = 100;
			this->error.setString("Brak odpowiedniej ilosci zlota!");
			this->newArcher = 0;
			this->newHorse = 0;
			this->newKnight = 0;
		}
	}
}

void CityState::renderButtons(RenderTarget* target)
{
	for (auto& i : this->buttons)
		i.second->render(target);
}

void CityState::hidingMainButtons()
{
	this->newKnightsText.setPosition(this->buttons["Deploy"]->button.getPosition().x + (this->buttons["Deploy"]->button.getGlobalBounds().width / 2) - this->newKnightsText.getGlobalBounds().width / 2, this->window->getSize().y * 0.25 + 10);
	this->newHorsesText.setPosition(this->buttons["Deploy"]->button.getPosition().x + (this->buttons["Deploy"]->button.getGlobalBounds().width / 2) - this->newKnightsText.getGlobalBounds().width / 2, this->window->getSize().y * 0.50 + 10);
	this->newArchersText.setPosition(this->buttons["Deploy"]->button.getPosition().x + (this->buttons["Deploy"]->button.getGlobalBounds().width / 2) - this->newKnightsText.getGlobalBounds().width / 2, this->window->getSize().y * 0.75 + 10);

	if (Town* ob = dynamic_cast<Town*>(this->city))
	{
		this->buttons["Training"]->button.setPosition(-300, 0);
		this->buttons["Deploy"]->button.setPosition(-300, 0);
		this->buttons["Training"]->setText();
		this->buttons["Deploy"]->setText();
	}
	else
	{
		stringstream ss;
		ss << "Ulepszenie miasta\n " << this->city->getGoldToUpgrade() << " zlota";
		this->buttons["Upgrade"]->button.setPosition(-300, 0);
		this->buttons["Training"]->button.setPosition(-300, 0);
		this->buttons["Deploy"]->button.setPosition(-300, 0);
		this->buttons["Upgrade"]->setText();
		this->buttons["Training"]->setText();
		this->buttons["Deploy"]->setText();
	}

	this->buttons["+knights"]->button.setPosition(this->window->getSize().x * 0.3125 + this->buttons["Training"]->getWidth() - 50, this->window->getSize().y * 0.25);
	this->buttons["+horses"]->button.setPosition(this->window->getSize().x * 0.3125 + this->buttons["Training"]->getWidth() - 50, this->window->getSize().y * 0.50);
	this->buttons["+archers"]->button.setPosition(this->window->getSize().x * 0.3125 + this->buttons["Training"]->getWidth() - 50, this->window->getSize().y * 0.75);
	this->buttons["-knights"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25);
	this->buttons["-horses"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.50);
	this->buttons["-archers"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.75);
	this->buttons["submit"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.75 + this->buttons["-archers"]->getHeight() + 10);

	this->buttons["+knights"]->setText();
	this->buttons["+horses"]->setText();
	this->buttons["+archers"]->setText();
	this->buttons["-knights"]->setText();
	this->buttons["-horses"]->setText();
	this->buttons["-archers"]->setText();
	this->buttons["submit"]->setText();

	
	this->knightsText.setPosition(this->window->getSize().x * 0.3125 + 25, this->window->getSize().y * 0.25 - 40);
	this->horsesText.setPosition(this->window->getSize().x * 0.3125 + 25, this->window->getSize().y * 0.5 - 40);
	this->archersText.setPosition(this->window->getSize().x * 0.3125 + 25, this->window->getSize().y * 0.75 - 40);
}

void CityState::showingMainButtons()
{
	if (Town* ob = dynamic_cast<Town*>(this->city))
	{
		this->buttons["Training"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25);
		this->buttons["Deploy"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.5);
		this->buttons["Training"]->setText();
		this->buttons["Deploy"]->setText();
	}
	else
	{
		stringstream ss;
		ss << "Ulepszenie miasta\n " << this->city->getGoldToUpgrade() << " zlota";
		this->buttons["Upgrade"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.25);
		this->buttons["Training"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.5);
		this->buttons["Deploy"]->button.setPosition(this->window->getSize().x * 0.3125, this->window->getSize().y * 0.75);
		this->buttons["Upgrade"]->setText();
		this->buttons["Training"]->setText();
		this->buttons["Deploy"]->setText();
	}

	this->buttons["+knights"]->button.setPosition(-100, this->window->getSize().y * 0.25);
	this->buttons["+horses"]->button.setPosition(-100, this->window->getSize().y * 0.50);
	this->buttons["+archers"]->button.setPosition(-100, this->window->getSize().y * 0.75);
	this->buttons["-knights"]->button.setPosition(-100, this->window->getSize().y * 0.25);
	this->buttons["-horses"]->button.setPosition(-100, this->window->getSize().y * 0.50);
	this->buttons["-archers"]->button.setPosition(-100, this->window->getSize().y * 0.75);
	this->buttons["submit"]->button.setPosition(-300, this->window->getSize().y * 0.75);
	this->buttons["+knights"]->setText();
	this->buttons["+horses"]->setText();
	this->buttons["+archers"]->setText();
	this->buttons["-knights"]->setText();
	this->buttons["-horses"]->setText();
	this->buttons["-archers"]->setText();
	this->buttons["submit"]->setText();

	this->newKnightsText.setPosition(-100, this->window->getSize().y * 0.25 + 10);
	this->newHorsesText.setPosition(-100, this->window->getSize().y * 0.50 + 10);
	this->newArchersText.setPosition(-100, this->window->getSize().y * 0.75 + 10);
	this->newArcher = 0;
	this->newHorse = 0;
	this->newKnight = 0;

	this->archersText.setPosition(-300, this->window->getSize().y * 0.25 - 30);
	this->knightsText.setPosition(-300, this->window->getSize().y * 0.5 - 30);
	this->horsesText.setPosition(-300, this->window->getSize().y * 0.75 - 30);
}