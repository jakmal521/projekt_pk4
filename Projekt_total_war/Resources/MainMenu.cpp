
#include "..\Headers\MainMenu.h"

//Konstruktory i destruktory
MainMenu::MainMenu(RenderWindow* window, stack<State*>* _states) : State(window, _states)
{
this->initBackground();
this->initFont();
this->initButtons();

}

MainMenu::~MainMenu()
{
	for (auto &i: this->buttons)
	{
		delete i.second;
	}
}
//Wyœwietlanie i updatowanie ekranu
void MainMenu::update()
{
	this->mousepos();
	this->updateButtons();
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

void MainMenu::updateButtons()
{
	for (auto& i : this->buttons)
		i.second->update(this->mouseposview);
	if (this->buttons["Menu"]->press())
		this->states->push(new GameState(this->window, this->states)); 
}

void MainMenu::renderButtons(RenderTarget* target)
{ 
	for (auto& i : this->buttons)
		i.second->render(target);
}

