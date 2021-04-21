#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Headers/District.h"

class Unit

{
public:
	//Konstruktor i destrukto
	Unit();
	~Unit();

	//Metody
	void update(sf::Vector2f mpos, District* districts);
	void render(sf::RenderTarget* target);
	void initPla(map<string, District*> districts);

private:
	//Wyglad
	sf::RectangleShape UnitShape;	//Kwadrat gracza
	sf::Texture UnitTexture;
	sf::Color UnitShapeColor;		//Kolor gracza
	sf::RectangleShape moveShape;	//Kwadrat kursora (czerwony X) poruszania siê po 1 klikniêciu
	sf::Texture moveTexture;
	sf::Color moveShapeColor;		//Kolor X-sa

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseHeld;

	//Parametry
	float moveSpeed;
};
