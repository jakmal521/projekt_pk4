#pragma once

#include "..\Headers\State.h"
#include "..\Headers\City.h"
#include "..\Headers\Town.h"
#include "..\Headers\Button.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
class CityState :
	public State
{
public:
	CityState(RenderWindow* window, Font _font, stack<State*>* _states, City& city, int gold);
	virtual ~CityState();

	void update();
	void render(RenderTarget* target = nullptr);
	void end();

private:
	//t³o
	RectangleShape background;
	Texture texture;
	//Czcionka
	Font font;
	//Przyciski
	map<string, Button*>buttons;
	void initButtons();
	void updateButtons(int playerGold);
	void renderButtons(RenderTarget* target);
	//Wyœwietlanie i update ekranu*/

	//Inicjacja t³a
	void initBackground(sf::RenderWindow* window);
	//Inicjalizacja tekstu i przycisków
	void initText(Font font, City& city);

	//Nazwa miasta
	Text greeting;
	//Informacje o mieœcie
	RectangleShape infoShape;
	void initInfo();
	void updateInfo();
	Text info;
	//Miasto
	City* city;
	//Tekst do pokazywania b³êdów
	Text error;
	int timeToSeeAlert;
	//Ile zlota ma wlasciciel
	int ownerGold;
};
