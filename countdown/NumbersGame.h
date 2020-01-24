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
    NumbersGame(const std::string& resourcePath,
                std::ostream& os,
                int numLarge,
                int numSmall);

    void initialize() override;
    
    void onBegin() override;
    
    int getScore(const std::string &answer) const override;
    
private:
    std::ostream& os;
    const int numLarge;
    const int numSmall;
    int target;
};


#endif /* NumbersGame_hpp */
