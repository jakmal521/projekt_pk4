#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Position
{
public:

	//Konstruktor i destruktor
	Position();
	Position(float pos, float speed);
	~Position();

	//Metody
	//virtual void update(float pos, float speed) = 0;
	//virtual void render(RenderWindow& window);

	virtual Vector2f GetPosition() {
		return this->shape.getPosition();
	}
protected:
	//Kszta³t w oknie
	sf::RectangleShape shape;
	float speed;
	float pos;
};