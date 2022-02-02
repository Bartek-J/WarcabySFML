#include "Textures.h"

Textures::Textures()
{
        whitePawn.setRadius(40.f);
        whitePawn.setFillColor(sf::Color(200, 200, 200));
        whitePawn.setOutlineThickness(3);
        whitePawn.setOutlineColor(sf::Color(100, 100, 100));

        blackPawn.setRadius(40.f);
        blackPawn.setFillColor(sf::Color(50, 50, 50));
        blackPawn.setOutlineThickness(3);
        blackPawn.setOutlineColor(sf::Color(20, 20, 20));

        whiteQueen.setRadius(40.f);
        whiteQueen.setFillColor(sf::Color(200, 200, 200));
        whiteQueen.setOutlineThickness(5);
        whiteQueen.setOutlineColor(sf::Color(249, 215, 28));

        blackQueen.setRadius(40.f);
        blackQueen.setFillColor(sf::Color(50, 50, 50));
        blackQueen.setOutlineThickness(5);
        blackQueen.setOutlineColor(sf::Color(249, 215, 28));

        background.setFillColor(sf::Color(199, 159, 95));
        background.setSize(sf::Vector2f(800, 800));

        rectangle.setFillColor(sf::Color(168, 143, 86));
        rectangle.setOutlineColor(sf::Color(143, 115, 50));
        rectangle.setOutlineThickness(2);

        font.loadFromFile("arial.ttf");

        sf::Image backgroundBoard;
        backgroundBoard.create(800, 800, sf::Color(255, 255, 255));
        sf::Color blackPixel(sf::Color(80, 80, 80));
        bool isBlack = false;
        for (int x = 0; x < 800; x++)
        {
            if (x % 100 == 0) isBlack = !isBlack;
            for (int y = 0; y < 800; y++)
            {
                if (y % 100 == 0) isBlack = !isBlack;
                if (isBlack)
                {
                    backgroundBoard.setPixel(x, y, blackPixel);
                }
            }
        }
        texture.loadFromImage(backgroundBoard);
        CheckersBoard.setTexture(texture);
}
