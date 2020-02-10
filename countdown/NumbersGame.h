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

#include "AbstractGame.h"

class NumbersGame : public AbstractGame<int>
{
public:
    explicit NumbersGame(std::mt19937& gen);

    void initialize(std::ostream& os, std::istream& is) override;
    
    std::string startMessage() const override;
    
    int getScore(const std::string& answer) const override;
    
    int getTarget() const;

private:
    bool validNumbersInAnswer(const std::string& answer) const;
    
private:
    int numLarge;
    int target;
};


#endif /* NumbersGame_hpp */
