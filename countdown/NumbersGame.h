//
//  NumbersGame.hpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef NumbersGame_hpp
#define NumbersGame_hpp

#include <array>
#include <ostream>

#include "AbstractGame.h"

class NumbersGame : public AbstractGame<int>
{
public:
    explicit NumbersGame(std::mt19937& gen, int numLarge, int numSmall);

    void initialize() override;
    
    std::string startMessage() const override;
    
    int getScore(const std::string& answer) const override;
    
    int getTarget() const;

private:
    bool validNumbersInAnswer(const std::string& answer) const;
    
private:
    const int numLarge;
    const int numSmall;
    int target;
};


#endif /* NumbersGame_hpp */
