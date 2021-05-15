#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <string>
using namespace sf;
using namespace std;
class Button
{
public:
	//Konstruktory i destruktory
	Button(float x, float y, float width, float height, Font* _font, string text, Color _color);
	~Button();
	//wyswietlanie na ekranie
	void render(RenderTarget* target);
	//Aktualizowanie przycisku
	void update(Vector2f mpos);
	//Akcesor
	bool press();
	//akcesory
	float getPosX();
	float getPosY();
	float getHeight();
	float getWidth();

private:
	//Wzor przycisku
	RectangleShape button;
	//Tresc na przycisku
	Text text;
	//Font
	Font* font;
	Color color;
	Color hover;
	//Czy ktoœ nacisn¹³
	bool pressed;
	//Dawanie tesktu na poprawn¹ pozycjê
	void setText();
	friend class Unit;
	friend class CityState;
};
