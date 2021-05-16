#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include "..\Headers\District.h"	//Wy�wietlanie i zarz�dzanie dystryktami
#include "..\Headers\Unit.h"		//Wy�wietlanie i zarz�dzanie jednostkami (graczem)
#include "..\Headers\Position.h"	//Pozycja view i headBar
#include "..\Headers\City.h"		//Wy�wietlanie miast
#include "..\Headers\CityState.h"	//Wy�wietlanie menu miasta i jego zarz�dzanie
#include "..\Headers\Enemy.h"		//Przeciwnicy
class GameState :
	public State
{
public:
	//Konstruktor i  destruktor
	GameState(RenderWindow* window, stack<State*>* _states, Font font);

	virtual ~GameState();

private:
	//Wy�wietlanie i update ekranu
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

	//T�o
	RectangleShape background;
	Texture texture;
	void initBackground();

	//Wektor region�w
	map<string, District*> districts;
	//updatowanie ilo�ci z�ota z podatk�w
	void updateGold();
	//Inicjalizacja region�w
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
	//Ile region�w ma gracz
	int amountOfdistricts();
	int amountOfEnemydistricts(Enemy* enemy);

	//Runda
	int turn = 1;

	//Przeciwnicy
	vector<pair<Enemy*, vector<Unit*>>> enemies;
	void initEnemies();
};
