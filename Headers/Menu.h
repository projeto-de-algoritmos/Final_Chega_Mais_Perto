#pragma once 

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Jogo.h"

class Menu{
public:
	void iniciaMenu(float width, float height);
	virtual ~Menu();

	void draw();
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	int fazMenu();
	int fazOpcoes();
	

private:
	sf::RenderWindow* window;
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[3];
	sf::Text opcoes[2]; 

};