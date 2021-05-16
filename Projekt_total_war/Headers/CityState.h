#pragma once

#include "..\Headers\State.h"
#include "..\Headers\City.h"
#include "..\Headers\Town.h"
#include "..\Headers\Button.h"
#include "..\Headers\Player.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
class CityState :
	public State
{
public:
	CityState(RenderWindow* window, Font _font, stack<State*>* _states, City& city, int gold, Player * player);

	~CityState();

	void update();
	void render(RenderTarget* target = nullptr);
	void end();

private:
	bool mouseHeld;

	//t³o
	RectangleShape background;
	Texture texture;
	//Czcionka
	Font font;
	//Przyciski
	map<string, Button*>buttons;

	void initButtons();
	void updateButtons();
	void renderButtons(RenderTarget* target);
	//Wyœwietlanie i update ekranu*/

	//Inicjacja t³a
	void initBackground(sf::RenderWindow* window);
	//Inicjalizacja tekstu i przycisków
	void initText(Font font, City& city);

	//Nazwa miasta
	Text greeting;
	//Informacje o mieœcie
	RectangleShape infoShape;
	void initInfo();
	void updateInfo();
	Text info;
	//Miasto
	City* city;
	//Tekst do pokazywania b³êdów
	Text error;
	int timeToSeeAlert;
	//Ile zlota ma wlasciciel
	int ownerGold;
	//Obiekt gracz
	Player* player;
	//Ukrywanie przycisków i pokazywanie g³ownych przycisków
	void hidingMainButtons();
	void showingMainButtons();
	// Sprawdzenie czy g³owne klawisze s¹ ukryte
	bool hiddenMainbuttons;
	//iloœæ jednostek do wytrenowania - wyœwietlanie
	Text newKnightsText;
	Text newHorsesText;
	Text newArchersText;
	//iloœæ jednostek do wytrenowania
	unsigned int newKnight;
	unsigned int newHorse;
	unsigned int newArcher;
	//Tekst jakie jednostki siê dodaje
	Text knightsText;
	Text horsesText;
	Text archersText;
};
