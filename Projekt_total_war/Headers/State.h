
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
	State(RenderWindow * window);
	~State();
	//Metody
	virtual void uptade()= 0;
	virtual void render(RenderTarget* target = nullptr) =0;
	virtual void end();
	//Akcesorry i settery
	const bool ifending();
	//Pozycja myszki
	Vector2i mouseposscreen;
	Vector2i mouseposwindow;
	Vector2f mouseposview;
	virtual void mousepos();

private: 
	//Zmienne
	vector<Texture*> textures;
	
	bool ifend;
	//Funkcje wirtualne potrzebne w pochodnych
	

};

