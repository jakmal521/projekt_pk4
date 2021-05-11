#include "..\Headers\GameState.h"
/*
Co ostatnio zrobione?
1. Komunikaty po wciœnieciu przycisków w miescie
2. Dzia³aj¹ce dodawanie i odejmowanie z³ota

TO DO LIST
1. Sztuczna inteligencja - w trakcie ;)
2. Dodawanie jednostek w mieœcie - w trakcie as well

Bugs:

Dodatkowe
1. Czy chcemy mieæ inne ikonki dla ró¿nego rodzaju miast???- jak zd¹¿ymy XD

*/

//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states, Font _font)
	: State(window, _states), howManyUnitsOnMap(5)
{
	this->initDis();
	this->initBackground();
	this->initView();
	this->initPlayer();
	this->initEnemies();
	this->initUnit(sf::Vector2f(0.f, 0.f), vector<int> {});
	this->font = _font;
	this->position->initHeadBar(&this->font, this->player);
}

GameState::~GameState()
{
	this->window->setView(this->view2);
	delete this->position;
}
//Wyœwietlanie i update ekranu
void GameState::update()
{
	this->mousepos();
	this->end();

	//update pozycji view i headBar
	position->update(this->amountOfdistricts(), this->mouseposview);

	//podœwietlanie dystryktów po najechaniu myszk¹
	for (auto& i : this->districts)
	{
		i.second->update(this->mouseposview);
	}

	//Sprawdzenie czy gracz zmieni³ obs³ugiwan¹ jednostkê
	this->changeUnit();

	//wyœwietlanie X-sa i jednostek na mapie
	for (auto& i : this->districts)
	{
		if (this->unit.size())
		{
			//Update wizualny wszystkich jednostek (bez mechaniki gry)
			for (int j = 0; j < unit.size(); j++)
			{
				this->unit[j]->updateAll(mouseposview, i.second->returnIsCursorOnDistrict());
			}

			//Update jednostki która zosta³a wybrana (tworzenie nowych armi, poruszanie itd.)
			if (this->whichUnit >= this->unit.size())
				this->whichUnit = 0;
			this->unit[this->whichUnit]->updateChoosen(mouseposview, i.second->returnIsCursorOnDistrict(), this->unit, i.second->cities);
			if (this->unit[whichUnit])
			{
				if (this->unit[this->whichUnit]->ifNewUnit())
				{
					initUnit(sf::Vector2f(this->unit[this->whichUnit]->UnitShape.getPosition().x + 30, this->unit[this->whichUnit]->UnitShape.getPosition().y + 30), vector<int> {});
				}
			}
			if (this->unit[this->whichUnit]->to_delete)
			{
				int a = this->unit[this->whichUnit]->nextUnit;
				if (this->whichUnit < a) a--;	//przy ³¹czeniu w górê trzeba odj¹æ 1 (np. gdy ³¹czymy z 1 do 3 to usunie nam 1-sz¹ jednostkê wiêc musimy wybraæ 2 miejse bo tam wskoczy jednostka nr.3)
				this->unit.erase(this->unit.begin() + this->whichUnit);
				this->whichUnit = a;
			}
		}
	}

	//Wyœwieltanie menu miasta po podwójnym klikniêciu i wyprowadzanie z niego wojska
	for (auto& i : this->districts)
	{
		if (i.second->cities.back()->isInCity())
		{
			this->window->setView(this->view2);

			this->states->push(new CityState(this->window, this->font, this->states, i.second->cities.back()[0], this->player->getGold()));
			i.second->cities.back()->setNotInCity();
		}
		if (i.second->cities.back()->isUnitsDeployed())
		{
			initUnit(i.second->cities.back()->getPosition(), i.second->cities.back()->howManyUnits());
			i.second->cities.back()->deleteTroops();
		}
		if (i.second->cities.back()->isToUpdate())
		{
			if (this->player->getGold() > i.second->cities.back()->getGoldToUpgrade())
			{
				if (Settlement* ob = dynamic_cast<Settlement*>(i.second->cities.back()))
				{
					this->player->setGold(this->player->getGold() - i.second->cities.back()->getGoldToUpgrade());
					i.second->cities.push_back(new Village(i.second->cities.back()));
					i.second->cities.back()->initCity(i.second->cities.front()->getPosition());
					i.second->cities.erase(i.second->cities.begin());
					this->position->update(amountOfdistricts(), this->mouseposview);
				}
				else if (Village* ob = dynamic_cast<Village*>(i.second->cities.back()))
				{
					this->player->setGold(this->player->getGold() - i.second->cities.back()->getGoldToUpgrade());
					i.second->cities.push_back(new Town(i.second->cities.back()));
					i.second->cities.back()->initCity(i.second->cities.front()->getPosition());
					i.second->cities.erase(i.second->cities.begin());
					this->position->update(amountOfdistricts(), this->mouseposview);
				}
			}
		}
	}

	//Rozpoczynanie nowej tury - poruszanie Ai
	if (this->position->isNextTurn())
	{
		cout << "Leci nastepna tura\n";
		for (int i = 0; i < this->enemies.size(); i++)
		{
			//Zauktalizowanie z³ota wroga
			this->enemies[i].first->updateEnemy(); //Do zrobienia update enemy
		//Zauktalizowanie jednostek wroga
			for (int j = 0; j < this->enemies[i].second.size(); j++)
			{
				this->enemies[i].second[j]->updateAiUnits(); //Do zrobienia updateAiUnits
			}
		}
	}

	//Wyœwietlanie pozycji myszki(czasem przydatne)
	//cout << this->mouseposview.x << " " << this->mouseposview.y << "\n";
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	//target->draw(this->background);

	//Renderowanie dystryktów
	for (auto& i : this->districts)
		i.second->render(this->window);

	//Renderowanie jednostek
	for (auto& j : this->unit)
		j->render(this->window);

	//Renderowanie przeciwników
	for (int k = 0; k < this->enemies.size(); k++)
	{
		for (int l = 0; l < this->enemies[k].second.size(); l++)
		{
			this->enemies[k].second[l]->render(window);
		}
	}

	//Ustawianie view
	this->view1.setCenter(position->GetPosition());
	this->window->setView(view1);
	this->position->render(target);
}

//Inicjalizacja regionów i miast
void GameState::initDis()
{
	string name;
	int points;
	char color;
	fstream plik("Resources/districts.txt");
	while (plik >> name)
	{
		plik >> color;
		this->districts[name] = new District(name);
		plik >> points;
		this->districts[name]->shape.setPointCount(points);
		for (int i = 0; i < points; i++)
		{
			float x, y;
			plik >> x >> y;

			this->districts[name]->shape.setPoint(i, Vector2f(x, y));
		}

		switch (color)
		{
		case 'c':this->districts[name]->shape.setFillColor(Color::Red); break;
		case 'b': this->districts[name]->shape.setFillColor(Color::White); break;
		case 'z':this->districts[name]->shape.setFillColor(Color::Green); break;
		}

		this->districts[name]->shape.setOutlineThickness(2);
		this->districts[name]->shape.setOutlineColor(Color(0, 0, 0, 160));

		//Zainicjowanie miasta w dystrykcie
		string line;
		std::getline(plik, line);
		this->districts[name]->initCity(line);
	}
	//cout << this->districts.size();

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
	if (Keyboard::isKeyPressed(Keyboard::Delete))
	{
		this->ifend = true;
	}
}

//Inicjalizacja jednostek
void GameState::initUnit(sf::Vector2f position, vector<int> amountOfTroops)
{
	if (this->unit.size() >= howManyUnitsOnMap)
	{
		cout << "Nie mozna miec na raz wiecej niz howManyUnitsOnMap(5) jednostek na mapie\n";
	}
	else
	{
		this->unit.push_back(new Unit(this->player->playerColor(), amountOfTroops));
		this->unit.back()->initUnit(position);
	}
}

//Zmienia wybran¹ jednostkê po klikniêciu na ni¹ lewym przyciskiem myszy i schowanie okienka split jeœli zosta³a wybrana inna
void GameState::changeUnit()
{
	for (int i = 0; i < this->unit.size(); i++)
	{
		if (this->unit[i]->UnitShape.getGlobalBounds().contains(this->mouseposview) && Mouse::isButtonPressed(Mouse::Left) && this->whichUnit != i && this->unit[i]->colorOfOwner == this->player->playerColor())
		{
			this->unit[this->whichUnit]->clicked = false;
			this->unit[this->whichUnit]->hideButtons();

			this->whichUnit = i;
			break;
		}
	}
}

//Incjalizacja widoku
void GameState::initView()
{
	this->view2 = window->getDefaultView();
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(400.f, 300.f));
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(800.f, 600.f));
	this->position = new Position(this->view1.getSize());
}

//Inicjalizacja danych gracza(z³oto itp.)
void GameState::initPlayer()
{
	this->player = new Player(Color::Red);
}
//Ile regionów ma gracz
int GameState::amountOfdistricts()
{
	int sum = 0;
	for (auto& i : this->districts)
		if (i.second->shape.getFillColor() == this->player->playerColor())
			sum++;

	return sum;
}

//Inicjacja przeciwników
void GameState::initEnemies()
{
	for (int i = 0; i < 2; i++) {
		this->enemies.push_back(pair<Enemy*, vector<Unit*>>(new Enemy(Color::Blue), { new Unit(Color::Blue, vector<int> {}) }));
	}
}

//Updatowanie ilosci zlota z podatków
void GameState::updateGold()
{
	int sum = 0;
	for (auto& i : this->districts)
	{
		if (i.second->cities[0]->colorOfOwner == this->player->playerColor())
			sum += i.second->cities[0]->population / 10;
	}
	this->player->setGold(this->player->getGold() + sum);
}