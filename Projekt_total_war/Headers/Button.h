#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sstream>  
class Button
{
public:
	//Konstruktory i destruktory
	Button(float x, float y, float width, float height, Font *_font, string text, Color _color);
	~Button();
	//wyswietlanie na ekranie
	void render(RenderTarget* target);
	//Aktualizowanie przycisku
	void uptade(Vector2f mpos);
private: 
	//Wzor przycisku
	RectangleShape button;
	//Tresc na przycisku
	Text text;
	//Font
	Font* font;
	Color color;
	Color hover;

};

