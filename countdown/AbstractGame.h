//
//  AbstractGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef AbstractGame_h
#define AbstractGame_h

#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "IGame.h"
#include "Timer.h"

template <typename T>
class AbstractGame : public IGame
{
public:
    AbstractGame(std::mt19937& gen)
    : gen(gen)
    {
    }
    std::string startMessage() const override { return std::string(); };
    std::string getGameBoard() const override;
    virtual void onStartRun() { };
    void run() override;
    virtual void onEndRun() { };
    std::string endMessage() const override { return std::string(); };
    virtual bool allowInterrupts() const { return false; };
    
protected:
    std::mt19937& gen; //Standard mersenne_twister_engine
    std::vector<T> gameBoard;
};

template<typename T>
void AbstractGame<T>::run()
{
    onStartRun();
    
    Timer t1;
    bool isInterruptable = allowInterrupts();
    while (t1.elapsed() < 30)
    {
        if (isInterruptable) //&& anyKeyPress)
          break;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    onEndRun();
}

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
