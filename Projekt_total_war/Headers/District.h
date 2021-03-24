#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace sf;
class District

{
public:
	//Kontruktor destruktor
	District();
	~District();

	//Settery
	void setColor();
private:
	//Kszta³t obszaru
	CircleShape shape;
	void initShape();

};

