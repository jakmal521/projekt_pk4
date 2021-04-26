#include "..\Headers\GameState.h"

//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states, Font _font)
	: State(window, _states), howManyUnitsOnMap(5)
{
	this->initDis();
	this->initBackground();
	this->initView();
	this->initUnit();
	this->initPlayer();
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
	position->update();

	//podœwietlanie dystryktów po najechaniu myszk¹
	for (auto& i : this->districts)
		i.second->update(mouseposview);

	//Sprawdzenie czy gracz zmieni³ obs³ugiwan¹ jednostkê
	this->changeUnit();
	//wyœwietlanie X-sa i jednostek na mapie
	for (auto& i : this->districts)
	{
		//for (int j = 0; j < unit.size(); j++)
		this->unit[this->whichUnit]->update(mouseposview, i.second);
		if (this->unit[this->whichUnit]->ifNewUnit())
		{
			if (this->unit.size() >= howManyUnitsOnMap)
			{
				cout << "Nie mozna miec na raz wiecej niz howManyUnitsOnMap(5) jednostek na mapie\n";
			}
			else
			{
				initUnit();
			}
		}
	}

	//Wyœwieltanie menu miasta po podwójnym klikniêciu
	for (auto& i : this->districts)
	{
		if (i.second->cities.back()->isInCity())
		{
			this->window->setView(this->view2);

			this->states->push(new CityState(this->window, this->font, this->states, i.second->cities.back()[0]));
			i.second->cities.back()->setNotInCity();
		}
	}

	//Wyœwietlanie pozycji myszki (czasem przydatne)
	//cout << this->mouseposwindow.x << " " << this->mouseposwindow.y << "\n";
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

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
			x = this->window->getSize().x * (x / 800);
			y = this->window->getSize().y * (y / 600);

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
void GameState::initUnit()
{
	this->unit.push_back(new Unit());
	this->unit.back()->initUnit(this->districts);
}

void GameState::changeUnit()
{
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
}

//Incjalizacja widoku
void GameState::initView()
{
	this->view2 = window->getDefaultView();
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(400.f, 300.f));
	this->position = new Position(this->view1.getSize());
}

//Inicjalizacja danych gracza(z³oto itp.)
void GameState::initPlayer()
{
	this->player = new Player();
}