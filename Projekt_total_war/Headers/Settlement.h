#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "..\Headers\City.h"
class Settlement : public City
{
public:
	//Konstruktor i destruktor
	Settlement(string name, Vector2f cityPoints, Color color);
	~Settlement();
	int getGoldToUpgrade();
private:
	int goldToUpdate;
};
