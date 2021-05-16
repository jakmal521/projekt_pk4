#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include "..\Headers\City.h"

using namespace sf;
using namespace std;
class Player
{
public:
	//Konstruktor i destruktor
	Player(Color color = Color::Black);
	~Player();
	//zwraca kolor gracza
	Color playerColor();
	//Ustawia ilosc zlota
	void setGold(int _gold);
	//Ile gracz ma z³ota
	int getGold();
private:
	//Atrybuty
	Color color;
	//Iloœæ z³ota
	int gold;

	friend class HeadBar;
	friend class GameState;
	friend class Unit;
	friend class Enemy;
};
