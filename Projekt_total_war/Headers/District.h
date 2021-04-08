#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include "..\Headers\City.h"
#include "..\Headers\Player.h"

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
	int returnIsPlayer();

	//Wyœwietlanie i updatowanie
	void update(Vector2f mpos);
	void render(RenderTarget* target = nullptr);

private:

	//Nazwa obszaru
	string name;

	//Czy gracz jest na tym polu
	int isPlayer;

	//Sprawdzenie czy przycisk myszy nie jest przytrzymywany
	bool mouseHeld;

	/*// Wyglad gracza
	sf::RectangleShape playerShape;
	sf::Texture playerTexture;*/

protected:
	//Miasta w obrêbie regionu
	vector< City*>cities;
};
