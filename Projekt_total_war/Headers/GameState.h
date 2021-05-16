#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include "..\Headers\District.h"	//Wyœwietlanie i zarz¹dzanie dystryktami
#include "..\Headers\Unit.h"		//Wyœwietlanie i zarz¹dzanie jednostkami (graczem)
#include "..\Headers\Position.h"	//Pozycja view i headBar
#include "..\Headers\City.h"		//Wyœwietlanie miast
#include "..\Headers\CityState.h"	//Wyœwietlanie menu miasta i jego zarz¹dzanie
#include "..\Headers\Enemy.h"		//Przeciwnicy
class GameState :
	public State
{
public:
	//Konstruktor i  destruktor
	GameState(RenderWindow* window, stack<State*>* _states, Font font);

	virtual ~GameState();

private:
	//Wyœwietlanie i update ekranu
	void update();
	void render(RenderTarget* target = nullptr);

	//Wychodzenie z rozgrywki
	void end();
	// Koniec rozgrywki
	bool won;
	bool ifPlayerWon();
	//Przechowuje pozycje i view
	View view1;
	View view2;
	Position* position;
	void initView();

	//Czcionka
	Font font;

	//Wektor regionów
	map<string, District*> districts;
	//updatowanie iloœci z³ota z podatków
	void updateGold();
	//Inicjalizacja regionów
	void initDis();

	//Klasa jednostki
	vector<Unit*> unit;
	void initUnit(sf::Vector2f position, vector<int> amountOfTroops, Color color);

	int howManyUnitsOnMap;
	int whichUnit = 0;
	void changeUnit();

	//Gracz
	Player* player;
	void initPlayer();
	//Ile regionów ma gracz
	int amountOfdistricts();
	int amountOfEnemydistricts(Enemy* enemy);

	//Runda
	int turn = 1;

	//Przeciwnicy
	vector<pair<Enemy*, vector<Unit*>>> enemies;
	void initEnemies();
};
