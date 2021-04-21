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
		void render(RenderTarget * target);
	private:
		//Kszta³t 
		RectangleShape barShape;
};

