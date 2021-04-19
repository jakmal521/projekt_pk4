#pragma once
#include "..\Headers\State.h"
#include "..\Headers\City.h"


#include <sstream>
#include <fstream>
#include <iostream>
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
	//t³o
	RectangleShape background;
	Texture texture;
	//Czcionka
	Font font;
	//Przyciski
   // map<string, Button*>buttons;
	/*void initButtons();
	void updateButtons();
	void renderButtons(RenderTarget* target);
	//Wyœwietlanie i update ekranu*/

	//Inicjacja t³a
	void initBackground(sf::RenderWindow* window);
	//Inicjalizacja tekstu i przycisków
	void initText(Font font, City& city);
	void initButtons();
	//Nazwa miasta
	Text cityName;
	//Czcionka 
	
};
