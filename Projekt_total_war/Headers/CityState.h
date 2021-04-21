#pragma once

#include "..\Headers\State.h"
#include "..\Headers\City.h"
#include "..\Headers\Button.h"



#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
class CityState :
	public State
{
public:
	CityState(RenderWindow* window, Font _font,stack<State*>* _states, City & city);
	virtual ~CityState();

	void update();
	void render(RenderTarget* target = nullptr);
	void end();
	
private:
	//t�o
	RectangleShape background;
	Texture texture;
	//Czcionka
	Font font;
	//Przyciski
    map<string, Button*>buttons;
	void initButtons();
	void updateButtons();
	void renderButtons(RenderTarget* target);
	//Wy�wietlanie i update ekranu*/

	//Inicjacja t�a
	void initBackground(sf::RenderWindow* window);
	//Inicjalizacja tekstu i przycisk�w
	void initText(Font font, City& city);
	
	//Nazwa miasta
	Text greeting;
	//Informacje o mie�cie
	RectangleShape infoShape;
	void initInfo();
	Text info;
	//Miasto 
	City* city;
	
};