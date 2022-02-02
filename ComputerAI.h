#pragma once
#include "Board.h"
#include <cstdlib>

class ComputerAI
{
public:
	std::string findBestMoveOnBoard(Board checkBoard, int depth );
	std::string findBestMoveOnBoardHard(Board checkBoard, int depth);
private:
	int returnEvalOfMove(std::string move);
	int minMaxFunction(std::vector<int>, bool max);
};

