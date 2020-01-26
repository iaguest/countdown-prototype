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
    AbstractGame(const std::string& resourcePath)
    : gen(std::random_device{}()), path(resourcePath)
    {
    }

    void onBegin() const override {};
    void onEnd() const override {};
    bool allowInterrupts() const override { return false; }
    int answerWaitTime() const override { return 10; }
    
    std::string getGameBoard() const override;
    
protected:
    std::mt19937 gen; //Standard mersenne_twister_engine
    const std::string& path;
    std::vector<T> gameBoard;
};


template <typename T>
std::string AbstractGame<T>::getGameBoard() const
{
    std::stringstream board;
    board << "[ ";
    std::for_each(begin(gameBoard), end(gameBoard),
                  [&board](const auto& elem){ board << elem << " "; });
    board << "]";
    return board.str();
}

#endif /* AbstractGame_h */
