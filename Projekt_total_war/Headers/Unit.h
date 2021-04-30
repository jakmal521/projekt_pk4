#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Headers/Button.h"

class Unit
{
public:
	//Konstruktor i destruktor
	Unit();
	~Unit();

	//Metody
	void updateChoosen(sf::Vector2f mpos, bool iCOD, vector <Unit*> &units);
	void updateAll(sf::Vector2f mpos, bool iCOD);
	void render(sf::RenderTarget* target);
	void initUnit();

	bool ifNewUnit();

private:
	//Wyglad gracza i X-sa poruszania
	sf::RectangleShape UnitShape;	//Kwadrat gracza
	sf::Texture UnitTexture;
	sf::Color UnitShapeColor;		//Kolor gracza
	sf::RectangleShape moveShape;	//Kwadrat kursora (czerwony X) poruszania siê po 1 klikniêciu
	sf::Texture moveTexture;
	sf::Color moveShapeColor;		//Kolor X-sa
	//Ilosc wojska
	int knights;
	int horses; //lol
	int archers;
	//Przyciski
	RectangleShape buttonBackground;
	RectangleShape buttonSplit;
	RectangleShape buttonCancel;
	sf::Font buttonsFont;
	void showButtons();
	void hideButtons();
	Text buttonBackgroundText;
	Font font;
	//Sprawdzenie czy jednostka jest podwójnie klikniêta lewym przyciskiem myszy
	bool clicked;

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseRightHeld;
	bool mouseLeftHeld;

	//Sprawdzenie czy chcemy stworzyæ now¹ jednostke na mapie
	bool drawButton;
	bool newUnit;

	//Clock
	sf::Clock clickClock;

	//Parametry
	float moveSpeed;
	friend class GameState;
	bool to_delete;
};
