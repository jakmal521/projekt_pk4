#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Headers/Button.h"
#include "../Headers/CityState.h"
#include "../Headers/Enemy.h"
#include "../Headers/District.h"

class Unit
{
public:
	//Konstruktor i destruktor
	Unit();
	Unit(Color color, vector<int> amountOfTroops, sf::Vector2f position);
	~Unit();

	//Metody
	void updateChoosen(sf::Vector2f mpos, bool iCOD, vector <Unit*>& units, vector<City*>& cities, vector<pair<Enemy*, vector<Unit*>>> enemies);
	void updateAll(sf::Vector2f mpos, bool iCOD);
	void render(sf::RenderTarget* target);

	bool ifNewUnit();

private:
	//Wyglad gracza i X-sa poruszania
	sf::RectangleShape UnitShape;	//Kwadrat gracza
	sf::Texture UnitTexture;
	sf::Color UnitShapeColor;		//Kolor gracza
	sf::RectangleShape moveShape;	//Kwadrat kursora (czerwony X) poruszania si� po 1 klikni�ciu
	sf::Texture moveTexture;
	sf::Color moveShapeColor;		//Kolor X-sa

	//Ilosc wojska
	int knights;
	int horses; //lol
	int archers;

	//Do kogo nale�y oddzia�
	Color colorOfOwner;

	//Przyciski
	RectangleShape buttonBackground;
	RectangleShape buttonSplit;
	RectangleShape buttonCancel;
	//teksty do klawiszy
	Text cancel;
	Text split;
	sf::Font buttonsFont;
	void showButtons();
	void hideButtons();
	Text buttonBackgroundText;
	Font font;

	//Sprawdzenie czy jednostka jest podw�jnie klikni�ta lewym przyciskiem myszy
	bool clicked;

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseRightHeld;
	bool mouseLeftHeld;

	//Sprawdzenie czy chcemy stworzy� now� jednostke na mapie
	bool drawButton;
	bool newUnit;

	//Clock
	sf::Clock clickClock;

	//Parametry
	float moveSpeed;
	friend class GameState;

	//Sprawdzenie czy trzeba usun�� jednostk�
	bool to_delete;

	//Wskazanie jednostki kt�r� b�dziemy kierowa� po usuni�ciu tej jednostki
	int nextUnit;

	//Ile mog� przej�� w jednym  do przej�cia
	float distance;
	void setDistance();
	friend class GameState;

	//Walka dw�ch oddzia��w
	void fight(Unit& enemyUnit);

	//Atakowanie miasta
	void cityAttack(City& city);

	//Poruszanie jednostkami Ai
	void updateAiUnits(int turn, vector <Unit*>* units, map<string, District*>* districts, vector<pair<Enemy*, vector<Unit*>>>* enemies, int whichEnemyIsChoosen);

	Vector2f closestEnemyCity(map<string, District*> districts, Unit* unit);
};
