#include "ComputerAI.h"

//function that seeks for best move on the board with selected depth
//How does it work?
//first it takes every possible moves
//next evaluate position for every move after making it
//and the last its choosing the best one
//if two moves have same evaluation then it takes random(out of two of them)
std::string ComputerAI::findBestMoveOnBoard(Board checkBoard, int depth)
{
    std::vector<std::vector<std::string>> predictionMoves;
    std::vector<int>evalute;
    predictionMoves.resize(depth+1);
    Board imaginaryBoard;
    checkBoard.copyCurrentBoard(imaginaryBoard);
    imaginaryBoard.allPossibleMovesOnBoard();
    std::string allMoves,move,p,path;
    int length = imaginaryBoard.getAllPossibleMoves().length(),eval;
    allMoves = imaginaryBoard.getAllPossibleMoves()+"m";
    size_t wheresM,wheresP;
    while (allMoves.length() >= 2)
    {
        if (allMoves[0] == 'p')
        {
            p = allMoves.substr(0, 3);
            allMoves.erase(0, 3);
        }
        else if (allMoves[0] == 'm')
        {
            move = p + "m";
            allMoves.erase(0, 1);
            wheresM = allMoves.find('m');
            wheresP = allMoves.find('p');
            if (wheresP < wheresM) wheresM = wheresP;
            move += allMoves.substr(0, wheresM);
            allMoves.erase(0, wheresM);
            predictionMoves[0].push_back(move);
        }
    }
    for (int i = 0; i < depth; i++)
    {
        int length = predictionMoves[i].size();
        for (int j = 0; j < length; j++)
        {
            checkBoard.copyCurrentBoard(imaginaryBoard);
            move = predictionMoves[i][j];
            p = move.substr(0, move.find('p'));
            int ptr = 0;
            int lng= p.length() - 1, dp = 0;
            for (int k = 0; k < lng;k++)
            {
                if (p[k] == '|')
                {
                imaginaryBoard.makeAImove(predictionMoves[dp][std::atoi(p.substr(ptr,k-ptr).c_str())]);
                ptr = k + 1;
                dp++;
                }
            }
            imaginaryBoard.makeAImove(move);
            imaginaryBoard.allPossibleMovesOnBoard();
            allMoves = imaginaryBoard.getAllPossibleMoves() + "m";
            path = p  + std::to_string(j) + "|";
            while (allMoves.length() >= 2)
            {
                if (allMoves[0] == 'p')
                {
                    p = allMoves.substr(0, 3);
                    allMoves.erase(0, 3);
                }
                else if (allMoves[0] == 'm')
                {
                    move = path + p + "m";
                    allMoves.erase(0, 1);
                    wheresM = allMoves.find('m');
                    wheresP = allMoves.find('p');
                    if (wheresP < wheresM) wheresM = wheresP;
                    move += allMoves.substr(0, wheresM);
                    allMoves.erase(0, wheresM);
                    predictionMoves[i + 1].push_back(move);
                    if (i + 1 == depth)
                    {
                        imaginaryBoard.makeAImove(move);
                        evalute.push_back(imaginaryBoard.evaluatePossition());
                    }
                    
                }
            }
        }
        if (predictionMoves[i + 1].size() == 0) break;
    }
    int depth2 = predictionMoves.size()-1;
    for (int i = depth2; i > 0; i--)
    {
        if (predictionMoves[i].size() == 0) depth2--;
    }
    if (depth2 < depth)  return findBestMoveOnBoard(checkBoard, depth-1); 
    if (depth == 0)
    {
        eval = 0;
    }
    else
    {
    eval = evalute[0];
    }
    length = evalute.size();
    int moveNumber = 0;
    for (int i = 1; i < length; i++)
    {
        if (evalute[i] < eval || (evalute[i] == eval && rand()%2 == 0))
        {
            eval = evalute[i];
            moveNumber = i;
        }
    }
    int i = 0;
    move = predictionMoves[depth][moveNumber];
        int chosenMove;
        if (move[0] == 'p') return move;
    while (true)
    {
        if (move[i] == '|')
        {
            chosenMove = std::atoi(move.substr(0, i).c_str());
            break;
        }
        i++;
    }
    return predictionMoves[0][chosenMove];
}

//second version of AI predictions
//It is based on MiniMax algorithm with few nuances
std::string ComputerAI::findBestMoveOnBoardHard(Board checkBoard, int depth)
{
    std::vector<std::vector<std::string>> predictionMoves;
    predictionMoves.resize(depth + 1);
    Board imaginaryBoard;
    checkBoard.copyCurrentBoard(imaginaryBoard);
    imaginaryBoard.allPossibleMovesOnBoard();
    std::string allMoves, move, p, path;
    int length = imaginaryBoard.getAllPossibleMoves().length(), eval;
    allMoves = imaginaryBoard.getAllPossibleMoves() + "m";
    size_t wheresM, wheresP;
    while (allMoves.length() >= 2)
    {
        if (allMoves[0] == 'p')
        {
            p = allMoves.substr(0, 3);
            allMoves.erase(0, 3);
        }
        else if (allMoves[0] == 'm')
        {
            move = p + "m";
            allMoves.erase(0, 1);
            wheresM = allMoves.find('m');
            wheresP = allMoves.find('p');
            if (wheresP < wheresM) wheresM = wheresP;
            move += allMoves.substr(0, wheresM);
            allMoves.erase(0, wheresM);
            predictionMoves[0].push_back(move);
        }
    }
    for (int i = 0; i < depth; i++)
    {
        int length = predictionMoves[i].size();
        for (int j = 0; j < length; j++)
        {
            checkBoard.copyCurrentBoard(imaginaryBoard);
            move = predictionMoves[i][j];
            p = move.substr(0, move.find('p'));
            int ptr = 0;
            int lng = p.length() - 1, dp = 0;
            for (int k = 0; k < lng; k++)
            {
                if (p[k] == '|')
                {
                    imaginaryBoard.makeAImove(predictionMoves[dp][std::atoi(p.substr(ptr, k - ptr).c_str())]);
                    ptr = k + 1;
                    dp++;
                }
            }
            imaginaryBoard.makeAImove(move);
            imaginaryBoard.allPossibleMovesOnBoard();
            allMoves = imaginaryBoard.getAllPossibleMoves() + "m";
            path = p + std::to_string(j) + "|";
            while (allMoves.length() >= 2)
            {
                if (allMoves[0] == 'p')
                {
                    p = allMoves.substr(0, 3);
                    allMoves.erase(0, 3);
                }
                else if (allMoves[0] == 'm')
                {
                    move = path + p + "m";
                    allMoves.erase(0, 1);
                    wheresM = allMoves.find('m');
                    wheresP = allMoves.find('p');
                    if (wheresP < wheresM) wheresM = wheresP;
                    move += allMoves.substr(0, wheresM);
                    allMoves.erase(0, wheresM);
                    imaginaryBoard.makeAImove(move);
                    if (i + 1 == depth)
                    {
                        imaginaryBoard.makeAImove(move);
                        move += "e" + std::to_string(imaginaryBoard.evaluatePossition());
                    }
                    predictionMoves[i + 1].push_back(move);
                }
            }
        }
        if (predictionMoves[i + 1].size() == 0) break;
    }
    int depth2 = predictionMoves.size() - 1;
    for (int i = depth2; i > 0; i--)
    {
        if (predictionMoves[i].size() == 0) depth2--;
    }
    if (depth2 < depth)  return findBestMoveOnBoardHard(checkBoard, depth - 1);
    if (depth == 0)
    {
        return predictionMoves[0][rand()%(predictionMoves[0].size())];
    }
    //i have all possible moves calculated
    int min;
    path = "";
    std::string path2;
    std::vector<int> evals;
    for (int i = predictionMoves.size() - 1; i > 0; i--)
    {
        path = predictionMoves[i][predictionMoves[i].size() - 1].substr(0, predictionMoves[i][predictionMoves[i].size() - 1].find('p'));
        int under = predictionMoves[i - 1].size() - 1;
        for (int j = predictionMoves[i].size() - 1; j >= 0; j--)
        {
            path2 = predictionMoves[i][j].substr(0, predictionMoves[i][j].find('p'));
            if (path2 == path)
            {
                evals.push_back(returnEvalOfMove(predictionMoves[i][j]));
            }
            else
            {
                path = path2;
                if (i % 2 == 1) min = minMaxFunction(evals, true);
                else min = minMaxFunction(evals, false);
                predictionMoves[i - 1][under] += "e" + std::to_string(min);
                under--;
                evals.clear();
                evals.push_back(returnEvalOfMove(predictionMoves[i][j]));
            }
            
        }
        if (i % 2 == 1) min = minMaxFunction(evals, true);
        else min = minMaxFunction(evals, false);
        predictionMoves[i - 1][under] += "e" + std::to_string(min);
        evals.clear();
    }
    min = returnEvalOfMove(predictionMoves[0][0]);
    int chosenMove = 0,tmp;
    for (int i = 1; i < predictionMoves[0].size(); i++)
    {
        tmp = returnEvalOfMove(predictionMoves[0][i]);
        if ((tmp < min) || (tmp == min && rand() % 2 == 1))
        {
            min = tmp;
            chosenMove = i;
        }
    }

    return predictionMoves[0][chosenMove];
}

//simple questions that returns evalaution for chosen move
//only works if evalution value is already saved in parsed string(move)
int ComputerAI::returnEvalOfMove(std::string move)
{
    int eval=0,tmp;
    move.erase(0, move.find('e'));
    for (int i = move.length() - 1; i > 0; i--)
    {
        tmp = (int)move[i] - 48;
        if (tmp == -3)
            eval *= -1;
        else eval = eval * 10 + tmp;
    }

    return eval;
}

//seeks for the lowest or biggest value from given vector
// bool max argument is reversed, it means max = true will return lowest value
int ComputerAI::minMaxFunction(std::vector<int> evals, bool max)
{
    int min=evals[0];
    if (!max)
    {
        for (int i = 1; i < evals.size(); i++)
        {
            if (min < evals[i]) min = evals[i];
        }
    }
    else
    {
        for (int i = 1; i < evals.size(); i++)
        {
            if (min > evals[i]) min = evals[i];
        }
    }
    return min;
}