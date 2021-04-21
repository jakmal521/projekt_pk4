#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
//#include "..\Headers\State.h"
#include "..\Headers\District.h"	//Wy�wietlanie i zarz�dzanie dystryktami
#include "..\Headers\Unit.h"		//Wy�wietlanie i zarz�dzanie jednostkami (graczem)
#include "..\Headers\Position.h"	//Pozycja view i headBar
#include "..\Headers\City.h"		//Wy�wietlanie miast
#include "..\Headers\CityState.h"	//Wy�wietlanie menu miasta i jego zarz�dzanie
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
	//Wektor region�w
	map<string, District*> districts;
	//Inicjalizacja region�w
	void initDis();
	//T�o
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
