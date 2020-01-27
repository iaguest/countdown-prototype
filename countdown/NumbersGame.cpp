//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <cctype>
#include <random>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

#include "NumbersGame.h"

namespace
{
    constexpr int numbersBoardSize = 6;
    const std::string operands("()+-*/");

    std::vector<std::string> tokenizeExpression(const std::string& expression, const std::unordered_set<char>& operands) {
        std::vector<std::string> tokens;
        std::string number;
        for (const auto& c : expression) {
            if (std::isdigit(c))
                number.push_back(c);
            if (!std::isspace(c) && operands.find(c) == end(operands))
                continue;
            if (number.size()) {
                tokens.push_back(number);
                number.clear();
            }
            if (!std::isspace(c))
              tokens.push_back(std::string(1, c));
        }
        if (number.size())
            tokens.push_back(number);
        return tokens;
    }

    std::string getPostFixExpression(const std::string& inFixExpression)
    {
        std::string postFix;
        
        /* This implementation does not implement composite functions,functions with variable number of arguments, and unary operators. */

//        while there are tokens to be read do:
//            read a token.
//            if the token is a number, then:
//                push it to the output queue.
//            if the token is a function then:
//                push it onto the operator stack
//            if the token is an operator, then:
//                while ((there is a function at the top of the operator stack)
//                       or (there is an operator at the top of the operator stack with greater precedence)
//                       or (the operator at the top of the operator stack has equal precedence and the token is left associative))
//                      and (the operator at the top of the operator stack is not a left parenthesis):
//                    pop operators from the operator stack onto the output queue.
//                push it onto the operator stack.
//            if the token is a left paren (i.e. "("), then:
//                push it onto the operator stack.
//            if the token is a right paren (i.e. ")"), then:
//                while the operator at the top of the operator stack is not a left paren:
//                    pop the operator from the operator stack onto the output queue.
//                /* if the stack runs out without finding a left paren, then there are mismatched parentheses. */
//                if there is a left paren at the top of the operator stack, then:
//                    pop the operator from the operator stack and discard it
//        /* After while loop, if operator stack not null, pop everything to output queue */
//        if there are no more tokens to read then:
//            while there are still operator tokens on the stack:
//                /* if the operator token on the top of the stack is a paren, then there are mismatched parentheses. */
//                pop the operator from the operator stack onto the output queue.
//        exit.
        
        return postFix;
    }
}


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
    auto foo = tokenizeExpression(answer, std::unordered_set<char>(begin(operands), end(operands)));
    for (auto& item : foo)
        std::cout << item << "\n";
    return 0;
}
