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
	//Wektor regionów
	map<string, District*> districts;
	//Inicjalizacja regionów
	void initDis();
	//Tło
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
	//Gracz
	Player* player;
	void initPlayer();
};
