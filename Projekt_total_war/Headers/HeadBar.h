#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;
class HeadBar
{
public:
	//Konstruktor i destruktor
	HeadBar(float x, float y);
	~HeadBar();
	//updatowanie i wyœwietlanie na ekranie
	void update();
	void render(RenderTarget* target);

	void setPos(sf::Vector2f viewPos, sf::Vector2f viewSize);
private:
	//Kszta³t
	RectangleShape barShape;
};
