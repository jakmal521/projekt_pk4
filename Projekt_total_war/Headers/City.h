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

	//Wyœwietlenie na ekranie
	void update(Vector2f mposC);
	void render(RenderTarget* target);

	//Inicjowanie miasta
	void initCity(sf::Vector2f cityPos);

	//Zwracanie czy wejœæ do miasta
	bool isInCity();
	//
	void setNotInCity();

	//Zwracanie czy wyprowadziæ wojsko
	bool isUnitsDeployed();

	//Zwracanie czy ulepszyæ miasto
	bool isToUpdate();

	//Zwracanie pozycji miasta
	sf::Vector2f getPosition();

	//Zwracanie iloœci wojska w mieœcie
	vector<int> howManyUnits();

	//Usuwanie wojska z miasta (liczb)
	void deleteTroops();

	virtual int getGoldToUpgrade() {
		return 0;
	};

protected:

	/*Mechanika*/
	//Zegar potrzebny do sprawdzenia czy by³ double click
	sf::Clock clickClock;
	//Czy mysz jest przytrzymywana
	bool mouseHeld;
	//Po³o¿enie
	sf::Vector2f cityPos;
	//Czy wejœæ do miasta
	bool doubleClicked;
	//Czy wypuœciæ jednostki z miasta
	int deployUnits;
	//Czy ulepszyæ miasto
	bool toUpdate;

	/*Wygl¹d*/
	//Tekstury
	sf::Texture cityIconTexture;
	sf::Color cityIconColor;
	sf::Texture insideCityTexture;

	sf::RectangleShape nameShape;
	sf::Font nameFont;
	sf::Text nameText;

	//Wygl¹d miasta
	RectangleShape cityIcon;
	Sprite sprite;

	//Kolor do kogo nale¿y miasto;
	Color colorOfOwner;

	/*Wartoœci w grze*/
	//Nazwa
	string cityName;
	//Iloœæ ludzi
	int population;
	//iloœæ ludzi jaka maksymalnie mo¿e mieszkaæ w mieœcie
	int populationMax;
	//Iloœæ rycerzy
	int knights;
	//iloœærycerzy jaka maksymalnie mo¿e byæ w mieœcie
	int knightsMax;
	//Iloœæ konnych
	int horses;
	//iloœæ konnychjaka maksymalnie mo¿e byæ w mieœcie
	int horsesMax;
	//Iloœæ ³uczników
	int archers;
	//iloœæ ³uczników jaka maksymalnie mo¿e byæ w mieœcie
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
