#pragma once
#include "..\Headers\City.h"
using namespace std;
using namespace sf;
class Town :
	public City
{
	//Konstruktor i destruktor
public:
	Town(string name, Vector2f cityPoints, Color color);
	Town(City* city);
	 ~Town();
	 
	// int getGoldToUpgrade() { return 0; }
	
};

