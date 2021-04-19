#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
//#include "..\Headers\State.h"
#include "..\Headers\District.h"
#include "..\Headers\Player.h"
#include "..\Headers\Position.h"
#include "..\Headers\City.h"
#include "..\Headers\CityState.h"
class GameState :
	public State
{
public:
	//Konstruktor i  destruktor
	GameState(RenderWindow* window, stack<State*>* _states,	Font font);

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
	vector<Player*> player;
	void initPlayer();
	//Przechowuje pozycje i view
	View view1;
	View view2;
	Position* position;
	void initView();
	//Czcionka
	Font font;
};
