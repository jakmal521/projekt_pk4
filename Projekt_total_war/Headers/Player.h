#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "..\Headers\District.h"

class Player
{
public:
	//Konstruktor i destrukto
	Player();
	~Player();

	void initPla(sf::Color color, sf::Vector2f vec);

	//Metody
	void update();
	void render(sf::RenderTarget* target);

private:
	//Wyglad
	sf::RectangleShape playerShape;
	sf::Texture playerTexture;

	//Parametry
	//int attack;
};
