#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "..\Headers\HeadBar.h"	//Wyświetlanie headBar

using namespace std;
using namespace sf;

class Position
{
public:

	//Konstruktor i destruktor
	Position();
	Position(sf::Vector2f viewSize);
	~Position();

	//Metody
	void update();
	void render(sf::RenderWindow* window);

	//Inicjalizacja headBar
	void initHeadBar();

	/*
		@param void
		Zwraca Vector pozycji kwadratu
	*/
	Vector2f GetPosition() {
		return this->shape.getPosition();
	}
protected:
	//Kształt kwadratu w oknie
	sf::RectangleShape shape;
	//HeaderBar
	HeadBar* headBar;
};