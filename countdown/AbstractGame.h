//
//  IGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef IGame_h
#define IGame_h

#include <string>
#include <vector>

template <typename T>
class AbstractGame
{
public:
    AbstractGame(const std::string& resourcePath)
    : gen(std::random_device{}()), path(resourcePath)
    {
    }

    virtual void initialize() = 0;
    virtual int calculateScore(const std::string& answer) const = 0;

    virtual bool allowInterrupts() const { return false; }
    virtual int answerWaitTime() const { return 10; }
    virtual void onBegin() {};
    virtual void onEnd() {};
    
    std::vector<T> getGameBoard() const { return gameBoard; }
    
protected:
    std::mt19937 gen; //Standard mersenne_twister_engine
    const std::string& path;
    std::vector<T> gameBoard;
};

#endif /* IGame_h */
