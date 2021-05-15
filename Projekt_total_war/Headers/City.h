#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;
class City
{
public:
	//Konstruktor i destruktor
	City();
	City(string name, int popMax, Vector2f cityPoints, Color color);
	virtual ~City();

	//Wy�wietlenie na ekranie
	void update(Vector2f mposC);
	void render(RenderTarget* target);

	//Inicjowanie miasta
	void initCity(sf::Vector2f cityPos);

	//Zwracanie czy wej�� do miasta
	bool isInCity();
	//
	void setNotInCity();

	//Zwracanie czy wyprowadzi� wojsko
	bool isUnitsDeployed();

	//Zwracanie czy ulepszy� miasto
	bool isToUpdate();

	//Zwracanie pozycji miasta
	sf::Vector2f getPosition();

	//Zwracanie ilo�ci wojska w mie�cie
	vector<int> howManyUnits();

	//Usuwanie wojska z miasta (liczb)
	void deleteTroops();

	virtual int getGoldToUpgrade() {
		return 0;
	};

protected:

	/*Mechanika*/
	//Zegar potrzebny do sprawdzenia czy by� double click
	sf::Clock clickClock;
	//Czy mysz jest przytrzymywana
	bool mouseHeld;
	//Po�o�enie
	sf::Vector2f cityPos;
	//Czy wej�� do miasta
	bool doubleClicked;
	//Czy wypu�ci� jednostki z miasta
	int deployUnits;
	//Czy ulepszy� miasto
	bool toUpdate;

	/*Wygl�d*/
	//Tekstury
	sf::Texture cityIconTexture;
	sf::Color cityIconColor;
	sf::Texture insideCityTexture;

	sf::RectangleShape nameShape;
	sf::Font nameFont;
	sf::Text nameText;

	//Wygl�d miasta
	RectangleShape cityIcon;
	Sprite sprite;

	//Kolor do kogo nale�y miasto;
	Color colorOfOwner;

	/*Warto�ci w grze*/
	//Nazwa
	string cityName;
	//Ilo�� ludzi
	int population;
	//ilo�� ludzi jaka maksymalnie mo�e mieszka� w mie�cie
	int populationMax;
	//Ilo�� rycerzy
	int knights;
	//ilo��rycerzy jaka maksymalnie mo�e by� w mie�cie
	int knightsMax;
	//Ilo�� konnych
	int horses;
	//ilo�� konnychjaka maksymalnie mo�e by� w mie�cie
	int horsesMax;
	//Ilo�� �ucznik�w
	int archers;
	//ilo�� �ucznik�w jaka maksymalnie mo�e by� w mie�cie
	int archersMax;
	//zmiany w populacji
	void updatePopulation();

	friend class CityState;
	friend class GameState;
	friend class Unit;
	friend class Village;
	friend class Town;
	friend class Settlement;
};
