#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "..\Headers\City.h"

using namespace sf;
using namespace std;
class District

{
public:
	//Kontruktor destruktor
	District(string name);
	~District();

	//Settery
	void setColor();
ConvexShape shape;
	//Wyœwietlanie i updatowanie
	void update(Vector2f mpos);
	void render(RenderTarget* target = nullptr);
private:
	//Nazwa obszaru
	string name;
	protected:
	//Miasta w obrêbie regionu
		vector< City*>cities;
	
};

