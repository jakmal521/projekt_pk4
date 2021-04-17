#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include "..\Headers\City.h"

using namespace sf;
using namespace std;
class District

{
public:
	//Kontruktor destruktor
	District(string name);
	~District();

	//Settery
	void setColor();
	ConvexShape shape; //Kszta³t dystryktu

	//Zwraca 0 albo 1 w zale¿noœci czy jest gracz czy go nie ma
	bool returnIsCursorOnDistrict();

	//Wyœwietlanie i updatowanie
	void update(Vector2f mpos);
	void render(RenderTarget* target = nullptr);
	sf::Vector2f returnPosition();

	//Nazwa obszaru
	string name;

	//Miasta
	//Miasta w obrêbie regionu
	vector<City*> cities;

private:

	//Czy kursor znajduje siê na dystrykcie
	bool isCursor;

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseHeld;

protected:
};
