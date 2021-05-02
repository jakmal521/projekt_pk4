#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
//#include "..\Headers\State.h"
#include "..\Headers\District.h"	//Wyświetlanie i zarządzanie dystryktami
#include "..\Headers\Unit.h"		//Wyświetlanie i zarządzanie jednostkami (graczem)
#include "..\Headers\Position.h"	//Pozycja view i headBar
#include "..\Headers\City.h"		//Wyświetlanie miast
#include "..\Headers\CityState.h"	//Wyświetlanie menu miasta i jego zarządzanie
#include "..\Headers\Enemy.h"		//Przeciwniy
class GameState :
	public State
{
public:
	//Konstruktor i  destruktor
	GameState(RenderWindow* window, stack<State*>* _states, Font font);

	virtual ~GameState();

private:
	//Wyświetlanie i update ekranu
	void update();
	void render(RenderTarget* target = nullptr);

	//Wychodzenie z rozgrywki
	void end();

	//Przechowuje pozycje i view
	View view1;
	View view2;
	Position* position;
	void initView();

	//Czcionka
	Font font;

	//Tło
	RectangleShape background;
	Texture texture;
	void initBackground();

	//Wektor regionów
	map<string, District*> districts;

	//Inicjalizacja regionów
	void initDis();

	//Klasa jednostki
	vector<Unit*> unit;
	void initUnit();
	int howManyUnitsOnMap;
	int whichUnit = 0;
	void changeUnit();

	//Gracz
	Player* player;
	void initPlayer();
	//Ile regionów ma gracz
	int amountOfdistricts();

	//Przeciwnicy
	vector<Enemy*> enemies;
	void initEnemies();
};
