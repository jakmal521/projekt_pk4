#pragma once
#include "..\Headers\State.h"

#include <sstream>
#include <fstream>
#include <iostream>
class CityState :
	public State
{
public:
	CityState(RenderWindow* window, stack<State*>* _states);
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
	void initFont();
};
