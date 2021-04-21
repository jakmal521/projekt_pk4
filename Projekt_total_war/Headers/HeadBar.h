#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <iostream>
 #include "..\Headers\Player.h"
using namespace std;
using namespace sf;
class HeadBar
{
public:
	//Konstruktor i destruktor
	HeadBar(float x, float y, Font* font, Player* player);
	~HeadBar();
	//updatowanie i wyœwietlanie na ekranie
	void update();
	void render(sf::RenderWindow* window);

	void setPos(sf::Vector2f viewPos, sf::Vector2f viewOrigin);
private:
	//Kszta³t
	RectangleShape barShape;
	//Wyœwietlanie info o graczu
	Text text;
	Player* player;
};
