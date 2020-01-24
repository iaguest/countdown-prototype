//
//  GameRunner.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef GameRunner_h
#define GameRunner_h

#include <chrono>
#include <thread>

#include "AbstractGame.h"
#include "Timer.h"

template <class T>
class GameRunner
{
public:
    
    GameRunner(AbstractGame<T>& game)
      : game(game)
    {
    }

    int execute()
    {
        game.initialize();
        
        game.onBegin();
        
        for (auto i: game.getGameBoard()) std::cout << i << " ";
        
        bool isInterruptable = game.allowInterrupts();
        
        std::cout << std::endl;
        std::cout << "Start 30 second countdown!" << std::endl;
        Timer t1;
        while (t1.elapsed() < 30)
        {
            if (isInterruptable) //&& anyKeyPress)
              break;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        std::cout << "Times up!" << std::endl;
        
        Timer t2;
        std::string answer;
        std::cout << "Enter answer: ";
        std::cin >> answer;
        if (t2.elapsed() > game.answerWaitTime())
            return 0;
        
        return game.getScore(answer);
        
        game.onEnd();
    }
    
private:
    
    AbstractGame<T>& game;
};

#endif /* GameRunner_h */
