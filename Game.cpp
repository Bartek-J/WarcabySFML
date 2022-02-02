#include "Game.h"

//Mother function that sets up the enviroment of application
void Game::startApp()
{
    srand(time(NULL));
    window.create(sf::VideoMode(800, 800), "Warcaby");
    window.setFramerateLimit(60);
    text.setFont(entity.font);
    text.setFillColor(sf::Color::White);
    setlocale(LC_ALL, "pl-PL");
    mainMenu();
}

//Sets text and draws it on screen
void Game::SetText(sf::String napis, int size, int posX, int posY)
{
    text.setString(napis);
    text.setCharacterSize(size);
    text.setPosition(sf::Vector2f(posX, posY));
    window.draw(text);
}

//Sets rectangle and draws it on screen
void Game::SetRectangle(int width, int height, int posX, int posY)
{
    entity.rectangle.setPosition(sf::Vector2f(posX, posY));
    entity.rectangle.setSize(sf::Vector2f(width, height));
    window.draw(entity.rectangle);
}

//Return current mouse position on screen
sf::Vector2f Game::getCurrentMousePosition()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    return window.mapPixelToCoords(pixelPos);
}

//Function handling Main Menu screen
void Game::mainMenu()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();    
            if (event.type == sf::Event::MouseButtonPressed)
                mainMenuNavigation(event.mouseButton.x, event.mouseButton.y, window.getSize().x, window.getSize().y);
        }
        window.draw(entity.background);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        SetText("Gra w warcaby", 62, 200, 150);
        text.setStyle(sf::Text::Regular);
        SetRectangle(190, 82, 300, 340);
        SetText("Start", 42, 350, 350);
        SetRectangle(190, 82, 300, 440);
        SetText(L"Jak graæ", 42, 320, 450);
        SetRectangle(190, 82, 300, 540);
        SetText(L"WyjdŸ", 42, 340, 550);
        window.display();
    }
}

//Function that lets player decide if he wants
//to play against other player or AI
bool Game::playWithAI()
{
    SetRectangle(400, 150, 200, 250);
    SetText("Wybierz tryb", 42, 288, 270);
    SetText("Player vs AI", 20, 250, 350);
    SetText("Player vs Player", 20, 400, 350);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f worldPos = getCurrentMousePosition();
                if (worldPos.y > 350 && worldPos.y < 370)
                {
                    if (worldPos.x > 250 && worldPos.x < 350)
                        return true;
                    else if (worldPos.x > 400 && worldPos.x < 500)
                        return false;
                }
            }
        }
    }
}

//Function handling playing chess
void Game::playGame(bool AI)
{
    ComputerAI compAI;
    Board gameBoard;
    gameBoard.makeBoard();
    int result,option;
    bool isDragging = false;
    int isGameRunning=0;
    while (window.isOpen())
    {
        if (AI && !gameBoard.whiteMove)
        {
            gameBoard.makeAImove(compAI.findBestMoveOnBoardHard(gameBoard, 4));
            gameBoard.allPossibleMovesOnBoard();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                gameBoard.makeBoard();
                isDragging = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                option = options();
                if (option == 1)
                {
                    gameBoard.makeBoard();
                    isDragging = false;
                }
                else if (option == 2)
                    return;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    result = gameBoard.whatSquareClicked(event.mouseButton.x, event.mouseButton.y, window.getSize().x, window.getSize().y);
                    if (result != 0)
                    {
                        isDragging = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left && isDragging == true)
                {
                    gameBoard.whatSquareReleased(event.mouseButton.x, event.mouseButton.y, window.getSize().x, window.getSize().y);
                    isDragging = false;
                }
            }
        }
        window.clear();
        window.draw(entity.CheckersBoard);
        int x, y;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                x = j * 100 + 10;
                y = i * 100 + 10;
                if (gameBoard.getBoard(i,j) == 0)
                {
                    continue;
                }
                else if (gameBoard.getBoard(i, j) == 1)
                {
                    entity.whitePawn.setPosition(sf::Vector2f(x, y));
                    window.draw(entity.whitePawn);
                }
                else if (gameBoard.getBoard(i, j) == -1)
                {
                    entity.blackPawn.setPosition(sf::Vector2f(x, y));
                    window.draw(entity.blackPawn);
                }
                else if (gameBoard.getBoard(i, j) == -3)
                {
                    entity.blackQueen.setPosition(sf::Vector2f(x, y));
                    window.draw(entity.blackQueen);
                }
                else if (gameBoard.getBoard(i, j) == 3)
                {
                    entity.whiteQueen.setPosition(sf::Vector2f(x, y));
                    window.draw(entity.whiteQueen);
                }
            }
        }

        isGameRunning = gameBoard.isGameOver();
        if (isGameRunning != 2)
        {
            if (gameOverScreen(isGameRunning))
            {
                gameBoard.makeBoard();
                isDragging = false;
            }
            else
            {
                return;
            }
        }

        if (isDragging)
        {
            sf::Vector2f worldPos = getCurrentMousePosition() + sf::Vector2f(-40.f, -40.f);
            if (result == 1)
            {
                entity.whitePawn.setPosition(sf::Vector2f(worldPos));
                window.draw(entity.whitePawn);
            }
            else if (result == -1)
            {
                entity.blackPawn.setPosition(sf::Vector2f(worldPos));
                window.draw(entity.blackPawn);
            }
            else if (result == -3)
            {
                entity.blackQueen.setPosition(sf::Vector2f(worldPos));
                window.draw(entity.blackQueen);
            }
            else if (result == 3)
            {
                entity.whiteQueen.setPosition(sf::Vector2f(worldPos));
                window.draw(entity.whiteQueen);
            }
        }
        window.display();

    }
}

//Indicates if any of buttons in main menu were clicked
void Game::mainMenuNavigation(int mouseX, int mouseY, int windowX, int windowY)
{
    sf::Vector2f worldPos = getCurrentMousePosition();
    int x = worldPos.x, y=worldPos.y;
    if (x > 300 && x < 420 && y>340)
    {
        if (y < 390)
        {
            bool ai = playWithAI();
            playGame(ai);
        }
        else if (y > 440 && y < 490)
            tutorial();
        else if (y > 540 && y < 590)
            window.close();
    }
}

//Screen that explains all the rules of the game
void Game::tutorial()
{
    window.clear();
    window.draw(entity.background);
    SetText(L"Zasady gry w warcaby(Warcaby niemieckie) \n1.Pionki poruszaj¹ siê o jedno pole po skosie i tylko do przodu \n2.Po dojœciu pionka na drugi koniec planszy zamienia siê w królow¹ \n3.Królowa porusza sie o dowoln¹ iloœæ pól, w ka¿dym kierunku \n4.Istnieje mo¿liwoœæ bicia do ty³u \n5.Ka¿dy ruch musi zostaæ wykonany w taki sposób, \naby zbiæ jak najwiêksza mo¿liwa iloœæ pionków \n6.Wygrywa ten kto zbije wszystkie pionki wroga \nlub osoba z wiêksz¹ iloœci¹ pionków w przypadku braku mo¿liwych ruchów\n7.Podczas gry naciœnij escape aby otworzyæ utawienia\n \nNaciœnij gdziekolwiek aby powróciæ",20,20,20);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); 
            if (event.type == sf::Event::MouseButtonPressed)
            {
                return;
            }
        }
    }

}

//game over screen
bool Game::gameOverScreen(int whoWon = 0)
{
    SetRectangle(400, 150, 200, 250);
    if (whoWon == 0)
        SetText("Draw", 42, 220, 270);
    else if (whoWon == 1)
        SetText("White won", 42, 220, 270);
    else
        SetText("Black won", 42, 220, 270);
    SetText(L"Naciœnij aby powróciæ", 20, 220, 320);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                return false;
            }
        }
    }
}

//activate in game options
int Game::options()
{
    SetRectangle(400, 150, 200, 250);
    SetText("Opcje", 42, 350, 270);
    SetText(L"Wznów", 20, 250, 350);
    SetText("Restart", 20, 370, 350);
    SetText("Menu", 20, 490, 350);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f worldPos = getCurrentMousePosition();
                if (worldPos.y > 350 && worldPos.y < 370)
                {
                    if (worldPos.x > 250 && worldPos.x < 320)
                        return 0;
                    else if (worldPos.x > 370 && worldPos.x < 440)
                        return 1;
                    else if (worldPos.x > 490 && worldPos.x < 540)
                        return 2;
                }
            }
        }
    }
}
