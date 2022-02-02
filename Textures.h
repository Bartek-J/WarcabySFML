#pragma once
#include "SFML/Graphics.hpp"
class Textures
{
public:
	sf::CircleShape whitePawn;
	sf::CircleShape blackPawn;
	sf::CircleShape whiteQueen;
	sf::CircleShape blackQueen;
	sf::RectangleShape background;
	sf::RectangleShape rectangle;
	sf::Texture texture;
	sf::Sprite CheckersBoard;
	sf::Font font;
	Textures();
};

