#include "Board.h"


//this is simple function that puts pawns in the starting positions
void Board::makeBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) && i < 3)
				board[i][j] = -1;
			else if (((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) && i > 4)
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}
	whiteMove = true;
	allPossibleMovesOnBoard();
	MovesWithoutCaptures = 0;
}

//Quality of life function usefull in states where i needed to check other than main boards
void Board::drawBoardConsole()
{
	std::cout << std::endl << "-----------" << std::endl;
	std::cout << std::setw(3);
	for (int i = 0; i < 8; i++)
		{
		for (int j = 0; j < 8; j++)
		{
			std::cout << board[i][j] << std::setw(3);
		}
			std::cout << std::endl;
		}
		std::cout << std::endl << "-----------" << std::endl;
}

//this function allows me to copy my main gameBoard position into temporary ones
void Board::copyCurrentBoard(Board &currentBoard)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			 currentBoard.board[i][j] = board[i][j];
		}
	}
	currentBoard.whiteMove = whiteMove;
	currentBoard.pickPawnX = pickPawnX;
	currentBoard.pickPawnY = pickPawnY;
	currentBoard.pickPawnValue = pickPawnValue;
	currentBoard.MovesWithoutCaptures = MovesWithoutCaptures;
}

/*
Schematic
p - new pawn
m - next possible move for mentioned pawn
k - killed pawns
n - next capture(for same pawn)
possible moves is function that seeks only for normal legal moves, discarding captures
i'm making another function for captures because of checkers rule that tells us
"You have to always make move that will captures the biggest possible amount of pawns"
*/
std::string Board::possibleMoves(int x, int y)
{
	std::string possibilities = "p" + std::to_string(y) + std::to_string(x);
	int val = board[y][x],i;
	if (val > 0 || val == -3)
	{
		if (y > 0)
		{
			if (x > 0 && board[y - 1][x - 1] == 0)
			{
				possibilities += "m" + std::to_string(y - 1) + std::to_string(x - 1);
				if (abs(val) == 3)
				{
					i = 2;
					while (true)
					{
						if (x > i - 1 && y > i - 1 && board[y - i][x - i] == 0)
						{
							possibilities += "m" + std::to_string(y - i) + std::to_string(x - i);
							i++;
						}
						else
						{
							break;
						}
					}
				}
			}
			if (x < 7 && board[y - 1][x + 1] == 0)
			{
				possibilities += "m" + std::to_string(y - 1) + std::to_string(x + 1);
				if (abs(val) == 3)
				{
					i = 2;
					while (true)
					{
						if (x < 8 - i  && y > i - 1 && board[y - i][x + i] == 0)
						{
							possibilities += "m" + std::to_string(y - i) + std::to_string(x + i);
							i++;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	if( val < 0 || val == 3)
	{
		if (y < 7)
		{
			if (x > 0 && board[y + 1][x - 1] == 0)
			{
				possibilities += "m" + std::to_string(y + 1) + std::to_string(x - 1);
				if (abs(val) == 3)
				{
					i = 2;
					while (true)
					{
						if (x > i - 1 && y < 8 - i && board[y + i][x - i] == 0)
						{
							possibilities += "m" + std::to_string(y + i) + std::to_string(x - i);
							i++;
						}
						else
						{
							break;
						}
					}
				}
			}
			if (x < 7 && board[y + 1][x + 1] == 0)
			{
				possibilities += "m" + std::to_string(y + 1) + std::to_string(x + 1);
				if (abs(val) == 3)
				{
					i = 2;
					while (true)
					{
						if (x < 8 - i && y < 8 - i && board[y + i][x + i] == 0)
						{
							possibilities += "m" + std::to_string(y + i) + std::to_string(x + i);
							i++;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
	if (possibilities.length() < 5) return "";
	return possibilities;
}

//function that checks for possible pawn captures (but only signle ones)
std::string Board::possibleCaptures(int x, int y)
{
	std::string moves="p" + std::to_string(y)+std::to_string(x);
	int val = board[y][x];
	//for now only checking for one jump
	if(abs(val) == 1)
	{
		if (y < 6)
		{
			if (x < 6 && val * board[y+1][x+1] < 0 && board[y + 2][x + 2] == 0)
			{
				moves += "m" + std::to_string(y + 2) + std::to_string(x + 2) + "k" + std::to_string(y + 1) + std::to_string(x + 1);
			}
			if (x > 1 && val * board[y + 1][x - 1] < 0 && board[y + 2][x - 2] == 0)
			{
				moves += "m" + std::to_string(y + 2) + std::to_string(x - 2) + "k" + std::to_string(y + 1) + std::to_string(x - 1);
			}
		}
		if (y > 1)
		{
			if (x < 6 && val * board[y - 1][x + 1] < 0 && board[y - 2][x + 2] == 0)
			{
				moves += "m" + std::to_string(y - 2) + std::to_string(x + 2) + "k" + std::to_string(y - 1) + std::to_string(x + 1);
			}
			if (x > 1 && val * board[y - 1][x - 1] < 0 && board[y - 2][x - 2] == 0)
			{
				moves += "m" + std::to_string(y - 2) + std::to_string(x - 2) + "k" + std::to_string(y - 1) + std::to_string(x - 1);
			}
		}
	}
	else if (abs(val) == 3)
	{
		std::string k;
		int i = 1;
		while (x + i < 6 && y + i < 6 && board[y+i][x+i] == 0)
		{
			i++;
		}
		if (val * board[y + i][x + i] < 0)
		{
			k = "k" + std::to_string(y + i) + std::to_string(x + i);
			i++;
			while (x + i < 8 && y + i < 8 && board[y + i][x + i] == 0)
			{
				moves += "m" + std::to_string(y + i) + std::to_string(x + i)+k;
				i++;
			}
		}

		i = 1;
		while (x - i > 1 && y + i < 6 && board[y+i][x-i] == 0)
		{
			i++;
		}
		if (val * board[y + i][x - i] < 0)
		{
			k = "k" + std::to_string(y + i) + std::to_string(x - i);
			i++;
			while (x - i > -1 && y + i < 8 && board[y + i][x - i] == 0)
			{
				moves += "m" + std::to_string(y + i) + std::to_string(x - i)+k;
				i++;
			}
		}

		i = 1;
		while (y - i > 1 && x + i < 6 && board[y - i][x + i] == 0)
		{
			i++;
		}
		if (val * board[y - i][x + i] < 0)
		{
			k = "k" + std::to_string(y - i) + std::to_string(x + i);
			i++;
			while (y - i > -1 && x + i < 8 && board[y - i][x + i] == 0)
			{
				moves += "m" + std::to_string(y - i) + std::to_string(x + i) + k;
				i++;
			}
		}

		i = 1;
		while (y - i > 1 && x - i > 1 && board[y - i][x - i] == 0)
		{
			i++;
		}
		if (val * board[y - i][x - i] < 0)
		{
			k = "k" + std::to_string(y - i) + std::to_string(x - i);
			i++;
			while (y - i > -1 && x - i > -1 && board[y - i][x - i] == 0)
			{
				moves += "m" + std::to_string(y - i) + std::to_string(x - i) + k;
				i++;
			}
		}
	}
	if (moves.length() < 5) return "";
	return moves;
}


//this function is made to be able to handle multiple captures in one move
//first it checks if any captures are possible
//then checks if after any capture there is another one
//and to do so im using possiblecaptures function
//for storing all data im going to use two dimensional vector
//every next depth will point to its master(previous capture move)
//at the end only moves with the biggest amount of captures are being taken into the consideration
//in order to be able to predict accurately all possible moves im going to use second temporary board, it will allow me to
//make moves to check for further possible captures and not make any changes in real gameBoard
std::string Board::bigAllCaptures(int x, int y)
{
	Board imaginatoryBoard;
	std::string tempMoves="",path="",allMoves="",move;
	int depth = 0, i = 0,tmp;
	size_t found;
	tempMoves = possibleCaptures(x, y);
	if (tempMoves != "")
	{
		std::vector<std::vector<std::string>> captureChain;
		captureChain.resize(8); //because thats the biggest possible amount of captures
		int length = tempMoves.length();
		for (int i = 3; i < length; i += 6)
		{
			captureChain[depth].push_back(tempMoves.substr(i, 6));
		}
		bool anyCapturesFound = true;
		while (anyCapturesFound)
		{
			anyCapturesFound = false;
			// next depths schema first parents id, second myx where, third kyx of killed pawn
			for (int i = 0; i < captureChain[depth].size(); i++)
			{
				path = captureChain[depth][i].substr(0, captureChain[depth][i].find('m'));
				copyCurrentBoard(imaginatoryBoard);
				int prevX = x, prevY = y, ptr = 0, lng = path.length() - 1, dp = 0;
				for (int j = 0; j < lng; j++)
				{
					if (path[j] == '|')
					{
						tmp = std::atoi(path.substr(ptr,j-ptr).c_str());
						ptr = j + 1;
						tempMoves = captureChain[dp][tmp];
						tempMoves.erase(0, tempMoves.find('m'));
						imaginatoryBoard.makeUnsafeMove(prevX, prevY, (int)tempMoves[2] - 48, (int)tempMoves[1] - 48);
						imaginatoryBoard.disappearPawn((int)tempMoves[5] - 48, (int)tempMoves[4] - 48);
						prevX = (int)tempMoves[2] - 48;
						prevY = (int)tempMoves[1] - 48;
						dp++;
					}
				}
				move = captureChain[depth][i];
				move.erase(0, move.find('m'));
				imaginatoryBoard.makeUnsafeMove(prevX, prevY, (int)move[2]-48, (int)move[1] - 48);
				imaginatoryBoard.disappearPawn((int)move[5] - 48, (int)move[4] - 48);
				prevX = (int)move[2] - 48;
				prevY = (int)move[1] - 48;
				tempMoves = imaginatoryBoard.possibleCaptures(prevX, prevY);
				if (tempMoves != "")
				{
					length = tempMoves.length();
					for (int k = 3; k < length; k += 6)
					{
						captureChain[depth+1].push_back(path+std::to_string(i)+"|"+tempMoves.substr(k, 6));
						anyCapturesFound = true;
					}
				}
			}
			depth++;
		}
		captureChain.resize(depth);
		depth--;
		allMoves = "p" + std::to_string(y) + std::to_string(x);
		for (int i = 0; i < captureChain[depth].size(); i++)
		{
			path = captureChain[depth][i].substr(0, captureChain[depth][i].find('m'));
			int ptr = 0, lng = path.length(),dp=0;
			for (int j = 0; j < lng; j++)
			{
				if (path[j] == '|')
				{
					tmp = std::atoi(path.substr(ptr, j - ptr).c_str());
					ptr = j + 1;
					tempMoves = captureChain[dp][tmp].erase(0, captureChain[dp][tmp].find('m'));
					if (dp != 0) tempMoves[0] = 'n';
					allMoves += tempMoves;
					dp++;
				}				
			}
			move = captureChain[depth][i];
			move.erase(0, move.find('m'));
			if (dp > 0)
			{
				move[0] = 'n';
			}
			allMoves += move;
		}
		captureChain.clear();
		return allMoves;
	}
	else
	{
		return "";
	}
}


//command used only by engine to reduce calculation time
void Board::makeUnsafeMove(int whoX, int whoY, int whereX, int whereY)
{
	int value = board[whoY][whoX];
	board[whoY][whoX] = 0;
	board[whereY][whereX] = value;
}

//Simple command to erase any pawn
void Board::disappearPawn(int x, int y)
{
	board[y][x] = 0;
}

//simple functino that checks if selected pawn is on the other side edge and if so then promoting it to queen
void Board::makeQueenIfPossible(int x, int y)
{
	int value = board[y][x];
	if (abs(value) != 3)
	{
		if ((y == 7 && value < 0) || (y == 0 && value > 0))
		{
			board[y][x] *= 3;
		}
	}
}

//fuction handling making moves for AI, it allows to skip all the safeguards made for user
void Board::makeAImove(std::string move)
{
	move.erase(0, move.find('p'));
	int pawn[4];
	pawn[0] = (int)move[1]-48;
	pawn[1] = (int)move[2]-48;
	pawn[2] = (int)move[4]-48;
	pawn[3] = (int)move[5]-48;
	makeUnsafeMove(pawn[1], pawn[0], pawn[3], pawn[2]);
	pawn[0] = pawn[2];
	pawn[1] = pawn[3];
	makeQueenIfPossible(pawn[1], pawn[0]);
	move.erase(0, 6);
	while (move.length() > 0)
	{
		if (move[0] == 'n')
		{
			pawn[2] = (int)move[1] - 48;
			pawn[3] = (int)move[2] - 48;
			makeUnsafeMove(pawn[1], pawn[0], pawn[3], pawn[2]);
			pawn[0] = pawn[2];
			pawn[1] = pawn[3];
			makeQueenIfPossible(pawn[1], pawn[0]);
		}
		else if (move[0] == 'k')
		{
			disappearPawn((int)move[2]-48,(int)move[1]-48);
		}
		move.erase(0, 3);
	}
	whiteMove = !whiteMove;
}

//this the main function that is looking for legal moves on board
//it is some sort of controller for the functions above
//first it checks for possible captures
//if there aren't any possible it checks for normal legal moves 
void Board::allPossibleMovesOnBoard()
{
	std::string allMoves = "";
	//first checking for all possible captures
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((board[i][j] > 0 && whiteMove) || (board[i][j] < 0 && !whiteMove))
				{
					allMoves += bigAllCaptures(j, i);
				}
			}
		}
	//if there are no possible captures, check for other legal moves
	if (allMoves == "")
	{
		MovesWithoutCaptures++;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((board[i][j] > 0 && whiteMove) || (board[i][j] < 0 && !whiteMove))
				{
					allMoves += possibleMoves(j, i);
				}
			}
		}
	}
	else
	{
		MovesWithoutCaptures = 0;
		int length = allMoves.length()-1,from = 0;
		std::string p,tmp;
		std::vector<std::string> movesCaptures;
		size_t m,pp;
		allMoves += "m";
		while (allMoves.length() > 1)
		{
			if (allMoves[0] == 'p')
			{
				p = allMoves.substr(0, 3);
				allMoves.erase(0, 3);
			}
			if (allMoves[0] == 'm')
			{
				allMoves.erase(0, 1);
				pp = allMoves.find('p');
				m = allMoves.find('m');
				if (pp < m) m = pp;
				movesCaptures.push_back(p+"m"+allMoves.substr(0, m));
				allMoves.erase(0, m);
			}
		}

		auto end = movesCaptures.end();
		for (auto it = movesCaptures.begin(); it != end; ++it) {
			end = std::remove(it + 1, end, *it);
		}
		movesCaptures.erase(end, movesCaptures.end());

		int longest = 0;
		for (int i = 0; i<movesCaptures.size();i++)
		{
			from = movesCaptures[i].length();
			if (from > longest)
			{
				longest = from;
			}
		}

		p = "";
		allMoves = "";
		for (int i = 0; i < movesCaptures.size(); i++)
		{
			if (movesCaptures[i].length() == longest)
			{
				if (p == movesCaptures[i].substr(0, 3))
				{
					movesCaptures[i].erase(0, 3);
				}
				else
				{
					p = movesCaptures[i].substr(0, 3);
				}
				allMoves += movesCaptures[i];
			}
		}
	}
	allPossibleMoves = allMoves;
}


//this function checks if move made by player is a legal or not
std::string Board::findMatchingMoves(int x, int y)
{
	std::string myPawn = std::to_string(pickPawnY) + std::to_string(pickPawnX) + std::to_string(y) + std::to_string(x), matchingMoves="";
	int length = allPossibleMoves.length();
	for (int i = 0; i < length; i++)
	{
		if (allPossibleMoves[i] == 'p' && allPossibleMoves[i + 1] == myPawn[0] && allPossibleMoves[i + 2] == myPawn[1])
		{
			int j = i + 3;
			while (j < length && allPossibleMoves[j] != 'p')
			{
				if (allPossibleMoves[j] == 'm' && allPossibleMoves[j + 1] == myPawn[2] && allPossibleMoves[j + 2] == myPawn[3])
				{
					do
					{
						matchingMoves += allPossibleMoves.substr(j, 3);
						j += 3;
					} while (j < length && allPossibleMoves[j] != 'm' && allPossibleMoves[j] != 'p');
				}
				else
				{
				j += 3;
				}
			}
			return matchingMoves;
		}
	}
	return "";
}


//after player grabs a pawn and moves it into diferent square this function makes move if possible
bool Board::makeMove(int x, int y)
{
	std::string possibilities;
	possibilities = findMatchingMoves(x, y);
	int length = possibilities.length();
	if (possibilities != "")
	{
		board[y][x] = pickPawnValue;
		if (length > 3 && possibilities[3] == 'k')
		{
			disappearPawn((int)possibilities[5] - 48, (int)possibilities[4] - 48);
		}
		if (length > 5 && possibilities[6] == 'n')
		{
			//here we have to implement code for another captures in same move
			std::string anotherMove = "p" + std::to_string(y) + std::to_string(x);
			pickPawnX = x;
			pickPawnY = y;
			while (possibilities.length() > 0)
			{
				if (possibilities[0] == 'n')
				{
					anotherMove += possibilities.substr(0, 6);
					possibilities.erase(0, 6);
				}
				else if (possibilities[0] == 'm')
				{
					possibilities.erase(0, 7);
					anotherMove += "m" + possibilities.substr(0, 5);
					possibilities.erase(0, 5);
				}
			}
			allPossibleMoves = anotherMove;
			return true;
		}
		makeQueenIfPossible(x, y);
		whiteMove = !whiteMove;
		allPossibleMovesOnBoard();
		return true;
	}
	return false;
}

//simple function to evaluate weather white or black is better in current position
int Board::evaluatePossition()
{
	int evaluation = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			evaluation += board[i][j];
		}
	}
	return evaluation;
}

//indicates what square was on board was clicked
//and saves it into memory 
int Board::whatSquareClicked(int x, int y, int width, int height)
{
	pickPawnX = x /(width / 8);
	pickPawnY  = y /(height / 8);
	pickPawnValue = board[pickPawnY][pickPawnX];
	if (pickPawnValue != 0)
	{
		board[pickPawnY][pickPawnX]=0;
	}
	return pickPawnValue;
}

//checks if dropped pawn(saved in previous function) can make selected move
void Board::whatSquareReleased(int x, int y, int width, int height)
{
	if(!makeMove(x / (width / 8),y / (height / 8)))
	{
		board[pickPawnY][pickPawnX] = pickPawnValue;
	}
}

int Board::getBoard(int i, int j)
{
	return board[i][j];
}

std::string Board::getAllPossibleMoves()
{
	return allPossibleMoves;
}

//simple function for handling ending the game
//rules are simple if there are no possible moves 
//then check who has more points(evaluate position) and this site is winning
int Board::isGameOver()
{
	if (MovesWithoutCaptures == 30) return 0;
	if (allPossibleMoves == "")
	{
		if (evaluatePossition() > 0) return 1;
		else if (evaluatePossition() == 0) return 0;
		else return -1;
	}
	return 2;
}

