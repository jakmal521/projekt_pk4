
#include "..\Headers\MainMenu.h"

//Konstruktory i destruktory
MainMenu::MainMenu(RenderWindow* window) : State(window)
{
this->initBackground();
this->initFont();
this->initButtons();

}

MainMenu::~MainMenu()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}
//Wyœwietlanie i uptade ekranu
void MainMenu::uptade()
{
	this->mousepos();
	this->uptadeButtons();
	this->end();
}

void MainMenu::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);
}
//Inicjacja t³a
void MainMenu::initBackground()
{
	stringstream ss;
	int random = rand() % 4 + 1;
	ss << "JPG/background_menu_" << random<<".jpg";
	this->texture.loadFromFile(ss.str());
	this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
	this->background.setTexture(&this->texture);
}
//Inicjalizacja czcionki
void MainMenu::initFont()
{
	this->font.loadFromFile("Fonts/RomanSD.ttf");
}
//Przyciski
void MainMenu::initButtons()
{
	this->buttons["Menu"] = new Button(500, 250, 200, 100, &this->font, "Nowa Gra", Color(0, 0, 0, 0));
	this->buttons["Opcje"] = new Button(500, 400, 200, 100, &this->font, "Opcje", Color(0, 0, 0, 0));

}

void MainMenu::uptadeButtons()
{
	for (auto& i : this->buttons)
		i.second->uptade(this->mouseposview);
}

void MainMenu::renderButtons(RenderTarget* target)
{ 
	for (auto& i : this->buttons)
		i.second->render(target);
}

