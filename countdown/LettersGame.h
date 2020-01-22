//
//  LettersGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef LettersGame_h
#define LettersGame_h

#include "IGame.h"

class LettersGame : public IGame<int>
{
    std::vector<int> getGameBoard() { return std::vector<int>{1,2,3}; }
    bool allowInterrupts() { return false; }
    int maxAnswerWaitTime() { return 5; }
    int calculateScore(std::string& answer) { return 20; }
};

#endif /* LettersGame_h */
