#include "..\Headers\GameState.h"



//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states, Font _font)
	: State(window, _states), howManyUnitsOnMap(5)
{
	this->initDis();
	this->initView();
	this->initPlayer();
	this->initEnemies();
	this->initUnit(sf::Vector2f(0.f, 0.f), vector<int> {10, 30, 0}, Color::Red);
	this->initUnit(sf::Vector2f(420.f, 50.f), vector<int> {10, 15, 12}, Color::Red);
	this->initUnit(sf::Vector2f(550.f, 520.f), vector<int> {0, 100, 0}, Color::Red);
	this->font = _font;
	this->position->initHeadBar(&this->font, this->player);
	this->won = false;
}

GameState::~GameState()
{
	for (auto& i : this->districts)
	{
		delete i.second;
	}
	for (auto& i : this->unit)
	{
		delete i;
	}
	for (auto& i : this->enemies)
	{
		for (auto& j : i.second)
			delete j;

		delete i.first;
	}
	delete this->player;
	this->window->setView(this->view2);
	delete this->position;
}
//Wyœwietlanie i update ekranu
void GameState::update()
{
	this->end();
	this->ifPlayerWon();
	if (!won)
	{
		this->mousepos();
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
				this->unit[this->whichUnit]->updateChoosen(mouseposview, i.second->returnIsCursorOnDistrict(), this->unit, i.second->cities, this->enemies);
				if (this->unit[whichUnit])
				{
					if (this->unit[this->whichUnit]->ifNewUnit() && (this->unit[this->whichUnit]->archers + this->unit[this->whichUnit]->knights + this->unit[this->whichUnit]->horses) > 6)
					{
						initUnit(sf::Vector2f(this->unit[this->whichUnit]->UnitShape.getPosition().x + 30, this->unit[this->whichUnit]->UnitShape.getPosition().y + 30), vector<int> {this->unit[this->whichUnit]->knights / 2, this->unit[this->whichUnit]->horses / 2, this->unit[this->whichUnit]->archers / 2}, this->unit[this->whichUnit]->colorOfOwner);
						this->unit[this->whichUnit]->archers -= this->unit[this->whichUnit]->archers / 2;
						this->unit[this->whichUnit]->knights -= this->unit[this->whichUnit]->knights / 2;
						this->unit[this->whichUnit]->horses -= this->unit[this->whichUnit]->horses / 2;
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
			if (i.second->cities.back()->isInCity() && this->player->playerColor() == i.second->cities.back()->colorOfOwner)
			{
				this->window->setView(this->view2);

				this->states->push(new CityState(this->window, this->font, this->states, i.second->cities.back()[0], this->player->gold, this->player));
				i.second->cities.back()->setNotInCity();
			}
			if (i.second->cities.back()->isUnitsDeployed())
			{
				if (i.second->cities.back()->colorOfOwner == Color::Red)
				{
					initUnit(i.second->cities.back()->getPosition(), i.second->cities.back()->howManyUnits(), i.second->cities.back()->colorOfOwner);
					i.second->cities.back()->deleteTroops();
				}
				else
				{
					initUnit(i.second->cities.back()->getPosition(), i.second->cities.back()->howManyUnits(), i.second->cities.back()->colorOfOwner);
					i.second->cities.back()->deleteTroops();
				}
			}
			if (i.second->cities.back()->isToUpdate())
			{
				
				if (this->player->getGold() > i.second->cities.back()->getGoldToUpgrade())
				{
					i.second->sizeOfCity++;
					if (Settlement* ob = dynamic_cast<Settlement*>(i.second->cities.back()))
					{
						i.second->cities.push_back(new Village(i.second->cities.back()));
						i.second->cities.back()->initCity(i.second->cities.front()->getPosition());

						i.second->cities.erase(i.second->cities.begin());
						this->position->update(amountOfdistricts(), this->mouseposview);
					}
					else if (Village* ob = dynamic_cast<Village*>(i.second->cities.back()))
					{
						if (i.second->cities.back()->colorOfOwner == Color::Red)
						{
							this->player->setGold(this->player->getGold() - i.second->cities.back()->getGoldToUpgrade());
						}
						i.second->cities.push_back(new Town(i.second->cities.back()));
						i.second->cities.back()->initCity(i.second->cities.front()->getPosition());

						i.second->cities.erase(i.second->cities.begin());
						this->position->update(amountOfdistricts(), this->mouseposview);
					}
				}
			}
		}
		for (auto& i : this->enemies)
		{
			for (int j = 0; j < i.second.size(); j++)
			{
				if (i.second[j]->to_delete)
				{
					i.second.erase(i.second.begin() + j);
					j--;
				}
			}
		}
		//Rozpoczynanie nowej tury - poruszanie Ai
		if (this->position->isNextTurn())
		{
			for (int i = 0; i < this->enemies.size(); i++)
			{
				//Zauktalizowanie z³ota wroga
				this->enemies[i].first->updateEnemy(this->districts);
				//Zauktalizowanie jednostek wroga
				for (int j = 0; j < this->enemies[i].second.size(); j++)
				{
					//for (auto& k : this->districts)

					this->enemies[i].second[j]->updateAiUnits(this->turn, &this->unit, &this->districts, &this->enemies, i, j); //Do zrobienia updateAiUnits
					for (int k = 0; k < unit.size(); k++)
					{
						if (this->unit[k]->to_delete)
						{
							int a = this->unit[this->whichUnit]->nextUnit;
							if (this->whichUnit < a) a--;	//przy ³¹czeniu w górê trzeba odj¹æ 1 (np. gdy ³¹czymy z 1 do 3 to usunie nam 1-sz¹ jednostkê wiêc musimy wybraæ 2 miejse bo tam wskoczy jednostka nr.3)
							this->unit.erase(this->unit.begin() + k);
							this->whichUnit = a;
						}
					}
				}
			}
			this->updateGold();

			for (int i = 0; i < unit.size(); i++)
				unit[i]->setDistance();

			cout << "Runda " << ++this->turn << "\n";
		}
	}
	else
	{
		Text endText;

		endText.setFont(this->font);
		endText.setString("Gratulacje, pokonales wszystkich! To czas zeby odpoczac, nacisnij klawisz delete aby wyjsc z gry. ");
		endText.setFillColor(Color::Red);
		endText.setCharacterSize(60);
		endText.setPosition(0, 0);
		this->window->draw(endText);
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	

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
	string fileName = ("Resources/districts.txt");
	smatch result;
	regex pattern("^.+\.txt$");
	if (!regex_match(fileName, result, pattern))

	{
		cout << "Nieprawidlowy plik TXT z mapa. Moga pojawic sie bledy!";
	}
	fstream plik;
	plik.open(fileName);
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
	

	plik.close();
}

//Wychodzenie z rozgrywki
void GameState::end()
{
	if (Keyboard::isKeyPressed(Keyboard::Delete))
	{
		this->ifend = true;
	}
}

bool GameState::ifPlayerWon()
{
	for (auto& i : this->districts)
	{
		if (i.second->shape.getFillColor() != this->player->playerColor())
			return false;
	}

	return true;
}

//Inicjalizacja jednostek
void GameState::initUnit(sf::Vector2f position, vector<int> amountOfTroops, Color color)
{
	if (color == Color::Red)
	{
		this->unit.push_back(new Unit(this->player->playerColor(), amountOfTroops, position));
	}
	else if (color == Color::White)
	{
		this->enemies[0].second.push_back(new Unit(color, amountOfTroops, position));
	}
	else if (color == Color::Green)
	{
		this->enemies[1].second.push_back(new Unit(color, amountOfTroops, position));
	}
	else
	{
		cout << "Cos nie tak w initUnit() w Gamestate.cpp\n";
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
	
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(1080.f, 720.f));
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

	for (map<string, District*>::iterator it = districts.begin(); it != districts.end(); it++)
	{
		if ((*it).second->shape.getFillColor() == this->player->playerColor())
		{
			sum++;
		}
	}

	return sum;
}

int GameState::amountOfEnemydistricts(Enemy* enemy)
{
	int sum = 0;
	for (map<string, District*>::iterator it = districts.begin(); it != districts.end(); it++)
	{
		if ((*it).second->shape.getFillColor() == enemy->playerColor())
			sum++;
	}

	return sum;
}

//Inicjacja przeciwników
void GameState::initEnemies()
{
	int one;
	int two;
	int three;
	float posX;
	float posY;
	string fileName = ("Resources/enemies.txt");
	smatch result;
	regex pattern("^.+\.txt$");
	if (!regex_match(fileName, result, pattern))

	{
		cout << "Nieprawidlowy plik TXT z przeciwnikami. Moga pojawic sie bledy!";
	}
	fstream plik;
	plik.open(fileName);
	while (plik >> one)
	{
		plik >> two;
		plik >> three;
		plik >> posX;
		plik >> posY;
		this->enemies.push_back(pair<Enemy*, vector<Unit*>>(new Enemy(Color(one, two, three, 255)), { new Unit(Color(one, two, three, 255), vector<int> {}, sf::Vector2f(posX, posY)) }));
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