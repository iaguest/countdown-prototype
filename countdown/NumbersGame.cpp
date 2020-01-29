//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <iostream>
#include <random>
#include <string>

#include "NumbersGame.h"
#include "NumbersGameUtils.hpp"

namespace {

constexpr int numbersBoardSize = 6;

}  // end namespace


NumbersGame::NumbersGame(const std::string& resourcePath,
                         int numLarge,
                         int numSmall)
  : AbstractGame(resourcePath),
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

std::string NumbersGame::startMessage() const
{
    return std::string("Target is: " + std::to_string(target));
}

int NumbersGame::getScore(const std::string &answer) const
{
    auto a = NumbersGameUtils::getPostFixExpression(NumbersGameUtils::tokenizeExpression( answer ));
    std::cout << std::accumulate(begin(a), end(a), std::string()) << std::endl;
    return 0;
}
