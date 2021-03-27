#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

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
//Kszta³t obszaru
	
};

