#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <stack>
#include "..\Headers\MainMenu.h"
using namespace std;
using namespace sf;
class Game
{
public:
	//Konstruktor i destruktor
	Game();
	~Game();
	void play();
private:
	//Okno g��wne
	RenderWindow* window;

	//Funckje inicjalizacyjne
	void initWindow();
	void initStates();
	

	//Funcje do zmiany zawarto�ci ekranu
	void update();
	void render();
	//Przechowywanie stan�w gry (menu, gra itp)
	stack<State*> states;
	//Wektor wielko�ci okna
	vector<VideoMode> videoMode;
};
