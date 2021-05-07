#include "..\Headers\City.h"
using namespace std;
using namespace sf;
class Village :
	public City
{
public:
	//konstruktor i destruktor
	Village(string name, Vector2f cityPoints, Color color);
	Village(City * city);
	~Village();
	int getGoldToUpgrade();
private: 
	int goldToUpgradde;
};


