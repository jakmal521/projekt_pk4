#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include "..\Headers\City.h"
#include "..\Headers\Settlement.h"
#include "..\Headers\Village.h"
#include "..\Headers\Town.h"

using namespace sf;
using namespace std;
class District

{
public:
	//Kontruktor destruktor
	District(string name);
	~District();

	//Settery
	
	ConvexShape shape; //Kszta�t dystryktu

	//Zwraca 0 albo 1 w zale�no�ci czy jest gracz czy go nie ma
	bool returnIsCursorOnDistrict();

	//Wy�wietlanie i updatowanie
	void update(Vector2f mpos);
	void render(RenderTarget* target = nullptr);
	sf::Vector2f returnPosition();
	void initCity(string line);

	//Nazwa obszaru
	string name;

	//Miasta
	//Miasta w obr�bie regionu
	vector<City*> cities;

	int sizeOfCity;

private:

	//Czy kursor znajduje si� na dystrykcie
	bool isCursor;

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseHeld;

protected:
};
