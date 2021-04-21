#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
//#include "..\Headers\State.h"
#include "..\Headers\District.h"	//Wyœwietlanie i zarz¹dzanie dystryktami
#include "..\Headers\Unit.h"		//Wyœwietlanie i zarz¹dzanie jednostkami (graczem)
#include "..\Headers\Position.h"	//Pozycja view i headBar
#include "..\Headers\City.h"		//Wyœwietlanie miast
#include "..\Headers\CityState.h"	//Wyœwietlanie menu miasta i jego zarz¹dzanie
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
	//Wektor regionów
	map<string, District*> districts;
	//Inicjalizacja regionów
	void initDis();
	//T³o
	RectangleShape background;
	Texture texture;
	void initBackground();
	//Wychodzenie z rozgrywki
	void end();
	//Klasa gracza
	vector<Unit*> unit;
	void initUnit();
	//Przechowuje pozycje i view
	View view1;
	View view2;
	Position* position;
	void initView();
	//Czcionka
	Font font;
};
