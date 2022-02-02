#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

//this is class handling, everyrhing that happens on game board
//it seeks for possible moves and makes them
class Board
{
public:
	int pickPawnX;
	int	pickPawnY;
	bool whiteMove;
	int pickPawnValue;
	int isGameOver();
	void makeBoard();
	int evaluatePossition();
	void drawBoardConsole();
	void allPossibleMovesOnBoard();
	void makeAImove(std::string move);
	void copyCurrentBoard(Board& currentBoard);
	int whatSquareClicked(int x, int y, int width, int height);
	void whatSquareReleased(int x, int y, int width, int height);
	int getBoard(int i, int j);
	std::string getAllPossibleMoves();
private:
	int MovesWithoutCaptures;
	int board[8][8];
	std::string allPossibleMoves;
	bool makeMove(int x, int y);
	void disappearPawn(int x, int y);
	void makeQueenIfPossible(int x, int y);
	std::string possibleMoves(int x, int y);
	std::string bigAllCaptures(int x, int y);
	std::string possibleCaptures(int x, int y);
	std::string findMatchingMoves(int x, int y);
	void makeUnsafeMove(int whoX, int whoY, int whereX, int whereY);
};