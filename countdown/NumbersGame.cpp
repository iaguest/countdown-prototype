//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <iostream>
#include <random>
#include <regex>
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

int NumbersGame::getScore(const std::string& answer) const
{
    double value;
    if (validNumbersInAnswer(answer) && NumbersGameUtils::tryEvaluateExpression(answer, value))
    {
        double abs_diff = abs(target - value);
        return abs_diff < 10 ? 10 - abs_diff : 0;
    }
    return 0;
}

bool NumbersGame::validNumbersInAnswer(const std::string& answer) const
{
    typedef std::sregex_iterator regex_iter;
    
    std::vector<int> answer_nums;
    std::regex re("\\d+");
    for (auto i = regex_iter(begin(answer), end(answer), re); i != regex_iter(); ++i)
        answer_nums.push_back(std::stoi(i->str())); 
    std::sort(begin(answer_nums), end(answer_nums));
    
    std::vector<int> gameBoardCopy(begin(gameBoard), end(gameBoard));
    std::sort(begin(gameBoardCopy), end(gameBoardCopy));
    
    std::vector<int> diffs;
    std::set_difference(begin(answer_nums), end(answer_nums), begin(gameBoardCopy), end(gameBoardCopy),                         std::back_inserter(diffs));
    
    return diffs.empty();
}
