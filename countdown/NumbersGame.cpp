//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <random>

#include "NumbersGame.h"

namespace
{
    const int numbersBoardSize = 6;
}


NumbersGame::NumbersGame(const std::string& resourcePath,
                         std::ostream& os,
                         int numLarge,
                         int numSmall)
  : AbstractGame(resourcePath),
    os(os),
    numLarge(numLarge),
    numSmall(numSmall)
{
}

void NumbersGame::initialize()
{
        std::array largeNumbers{ 25, 50, 75, 100 };
        std::array smallNumbers{ 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 8 , 8 , 9 , 9 , 10 , 10 };
    
        std::shuffle(begin(smallNumbers), end(smallNumbers), gen);
    
        std::size_t numLargeNumbers = std::uniform_int_distribution<>(0, largeNumbers.size())(gen);
    
        std::sample(rbegin(largeNumbers), rend(largeNumbers), std::back_inserter(gameBoard),
                    numLargeNumbers, gen);
        std::sample(smallNumbers.begin(), smallNumbers.end(), std::back_inserter(gameBoard),
                    numbersBoardSize - numLargeNumbers, gen);
    
        target = std::uniform_int_distribution<>(100, 999)(gen);
}

void NumbersGame::onBegin()
{
    os << "Target is: " << target << std::endl;
}

int NumbersGame::getScore(const std::string &answer) const
{
    return 0;
}
