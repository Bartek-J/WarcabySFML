#pragma once
#include <locale>
#include "Board.h"
#include "ComputerAI.h"
#include "Textures.h"
class Game
{
public:
	void startApp();
private:
	sf::RenderWindow window;
	sf::Text text;
	Textures entity;
	void SetText(sf::String napis, int size, int posX, int posY);
	void SetRectangle(int width, int height, int posX, int posY);
	sf::Vector2f getCurrentMousePosition();
	int options();
	void mainMenu();
	void tutorial();
	bool playWithAI();
	void playGame(bool AI);
	bool gameOverScreen(int whoWon);
	void mainMenuNavigation(int mouseX, int mouseY, int windowX, int windowY);
};

