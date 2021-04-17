#pragma once
#include "..\Headers\City.h"
class Settlement : public City
{
public:
	//Konstruktor i destruktor
	Settlement(std::string name, int popMax);
	~Settlement();
	//Wy�wietlanie i updatowanie miasta
	void update();
	void render(RenderTarget* target);
};
