#include "..\Headers\GameState.h"

//Konstruktory i destruktory
GameState::GameState(RenderWindow* window, stack<State*>* _states, Font _font) : State(window, _states)
{
	this->initDis();
	this->initBackground();
	this->initView();
	this->initUnit();
	this->initHeadBar();
	this->font = _font;
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
	for (auto& i : this->districts)
	{
		if (i.second->cities.back()->isInCity())
		{
			this->window->setView(this->view2);

			this->states->push(new CityState(this->window, this->font, this->states, i.second->cities.back()[0]));
			i.second->cities.back()->setNotInCity();
		}
	}
	for (auto& i : this->districts)
		i.second->update(mouseposview);
	for (auto& i : this->districts)
		this->unit.back()->update(mouseposview, i.second);
	position->update();
	this->headBar->setPos(this->view1.getCenter(), this->view1.getSize()); //pobiera œrodek wiêc trzeba trochê zmodyfikowaæ w funkcji

	//Wyœwietlanie pozycji myszki (czasem przydatne)
	//cout << this->mouseposwindow.x << " " << this->mouseposwindow.y << "\n";
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	for (auto& i : this->districts)
		i.second->render(this->window);
	for (auto& j : this->unit)
		j->render(this->window);

	this->view1.setCenter(position->GetPosition());

	this->window->setView(view1);
	this->headBar->render(window);
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

//Inicjalizacja gracza
void GameState::initUnit()
{
	this->unit.push_back(new Unit());
	this->unit.back()->initPla(this->districts);
}

//Incjalizacja widoku
void GameState::initView()
{
	this->view2 = window->getDefaultView();
	this->view1 = View(Vector2f(0.f, 0.f), Vector2f(400.f, 300.f));
	this->position = new Position();
}
//Head bar
void GameState::initHeadBar()
{
	this->headBar = new HeadBar(this->view1.getSize().x, this->view1.getSize().y);
}