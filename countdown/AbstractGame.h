//
//  AbstractGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef AbstractGame_h
#define AbstractGame_h

#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "IGame.h"

template <typename T>
class AbstractGame : public IGame
{
public:
    AbstractGame(std::mt19937& gen)
    : gen(gen)
    {
    }

    std::string getGameBoard() const override;
    std::string startMessage() const override { return std::string(); };
    std::string endMessage() const override { return std::string(); };
    bool allowInterrupts() const override { return false; }
    int answerWaitTime() const override { return 1000; }
    
protected:
    std::mt19937& gen; //Standard mersenne_twister_engine
    std::vector<T> gameBoard;
};


template <typename T>
std::string AbstractGame<T>::getGameBoard() const
{
    std::stringstream board;
    std::for_each(begin(gameBoard), end(gameBoard),
                  [&board](const auto& elem){ board << elem << " "; });
    std::string boardStr = board.str();
    return boardStr.empty() ? boardStr : std::string(begin(boardStr), --end(boardStr));
}

#endif /* AbstractGame_h */
