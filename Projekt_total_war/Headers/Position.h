#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Position
{
public:

	//Konstruktor i destruktor
	Position();
	~Position();

	//Metody
	void update();
	//void render(RenderWindow& window); //na razie zbêdny

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
};