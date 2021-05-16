#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stack>
#include <map>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class State
{
public:
	//Okno
	RenderWindow* window;
	//kontruktor i destruktor
	State(RenderWindow* window, stack<State*>*& _states);
	virtual ~State();
	//Metody
	virtual void update() = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
	//Akcesorry i settery
	const bool ifending();
	void endState()
	{
		this->ifend = true;
	}

protected:
	//Zmienne
	vector<Texture*> textures;

	bool ifend;
	//Przechowywanie innych stanów
	stack<State*>* states;

	//Pozycja myszki
	Vector2i mouseposscreen;
	Vector2i mouseposwindow;
	Vector2f mouseposview;
	virtual void mousepos();
};
