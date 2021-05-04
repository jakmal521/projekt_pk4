#include "..\Headers\GameState.h"

//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states, Font _font)
	: State(window, _states), howManyUnitsOnMap(5)
{
	this->initDis();
	this->initBackground();
	this->initView();
	this->initPlayer();
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
	position->update(this->amountOfdistricts());

	//podœwietlanie dystryktów po najechaniu myszk¹
	for (auto& i : this->districts)
	{
		i.second->update(mouseposview);
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

			this->states->push(new CityState(this->window, this->font, this->states, i.second->cities.back()[0]));
			i.second->cities.back()->setNotInCity();
		}
		if (i.second->cities.back()->isUnitsDeployed())
		{
			initUnit(i.second->cities.back()->getPosition(), i.second->cities.back()->howManyUnits());
			i.second->cities.back()->deleteTroops();
		}
	}

	if (/*jakiœ przycisk który now¹ turê zacznie*/ 0)
	{
		for (auto& i : this->enemies)
			i->update();
		for (auto& i : this->unit)
			i->setDistance();
	}
	//Wyœwietlanie pozycji myszki (czasem przydatne)
	cout << this->mouseposview.x << " " << this->mouseposview.y << "\n";
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
	fstream plik("Resources/districts.txt");
	while (plik >> name)
	{
		this->districts[name] = new District(name);
		plik >> points;
		this->districts[name]->shape.setPointCount(points);
		for (int i = 0; i < points; i++)
		{
			float x, y;
			plik >> x >> y;
			/*x = this->window->getSize().x * (x / 800);
			y = this->window->getSize().y * (y / 600);*/

			this->districts[name]->shape.setPoint(i, Vector2f(x, y));
		}
		//this->districts[name]->shape.scale(0.5, 0.5);
		this->districts[name]->shape.setFillColor(Color::Black);
		this->districts[name]->shape.setOutlineThickness(2);
		this->districts[name]->shape.setOutlineColor(Color(222, 184, 135, 160));

		//Zainicjowanie miasta w dystrykcie
		string line;
		getline(plik, line);
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

	/*
	int a = this->whichUnit;
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		this->whichUnit = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		this->whichUnit = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		this->whichUnit = 2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		this->whichUnit = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		this->whichUnit = 4;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num6))
	{
		this->whichUnit = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num7))
	{
		this->whichUnit = 6;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num8))
	{
		this->whichUnit = 7;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num9))
	{
		this->whichUnit = 8;
	}

	if (this->whichUnit >= this->unit.size())
	{
		this->whichUnit = a;
	}
	*/
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
	this->player = new Player(Color::Black);
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
	for (int i = 0; i < 2; i++)
	{
		this->enemies.push_back(new Enemy(Color::Blue));
	}
}