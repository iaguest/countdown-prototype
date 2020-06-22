//
//  IGame.h
//  countdown
//
//  Created by Ian Guest on 26/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef IGame_h
#define IGame_h

#include <iostream>
#include <string>

class IGame
{
public:
    IGame() = default;
    virtual ~IGame() {}
    
    IGame(IGame&) = delete;
    IGame& operator=(const IGame&) = delete;
    
    virtual void initialize(std::ostream& os, std::istream& is) = 0;
    virtual std::string startMessage() const = 0;
    virtual std::string getGameBoard() const = 0;
    virtual void run() = 0;
    virtual std::string endMessage() const = 0;
    // Score -1 on timeout
    virtual int getScore(const std::string& answer,
                         const double answerTime) const = 0;
};

#endif /* IGame_h */
