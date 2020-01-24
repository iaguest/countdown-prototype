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
class IGame
{
public:
    virtual std::vector<T> getGameBoard() const = 0;
    virtual bool allowInterrupts() const = 0;
    virtual int answerWaitTime() const = 0;
    virtual int calculateScore(const std::string& answer) const = 0;
};

#endif /* IGame_h */
