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
#include <vector>

#include "IGame.h"
#include "Timer.h"

class GameRunner
{
public:
    
    GameRunner(std::vector<IGame*> games)
      : games(games)
    {
    }

    int execute()
    {
        int score = 0;
        for (auto& game: games) {
            game->initialize();
            
            std::string startMessage = game->startMessage();
            if (!startMessage.empty())
                std::cout << game->startMessage() << std::endl;
            
            std::cout << game->getGameBoard();
            
            bool isInterruptable = game->allowInterrupts();
            
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
            
            std::string endMessage = game->endMessage();
            if (!endMessage.empty())
                std::cout << game->endMessage() << std::endl;
            
            if (t2.elapsed() <= game->answerWaitTime()) {
                score += game->getScore(answer);
            }
            std::cout << "Current score: " << score << std::endl << std::endl;
        }
        return score;
    }
    
private:
    
    std::vector<IGame*> games;
};

#endif /* GameRunner_h */
