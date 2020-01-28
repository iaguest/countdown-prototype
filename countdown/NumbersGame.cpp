//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <cctype>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <unordered_set>

#include "NumbersGame.h"

namespace {

constexpr int numbersBoardSize = 6;
const std::map<char, int> operatorPrecedence{ {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1} };

std::unordered_set<char> delimeters()
{
    std::unordered_set<char> delimeters{ '(', ')', ' ' };
    std::transform(begin(operatorPrecedence), end(operatorPrecedence), std::inserter(delimeters, end(delimeters)),
                   [](const auto& pair) { return pair.first; });
    return delimeters;
}

std::vector<std::string> tokenizeExpression(const std::string& expression, const std::unordered_set<char>& delimeters) {
    std::vector<std::string> tokens;
    std::string number;
    for (const auto& c : expression) {
        if (std::isdigit(c))
            number.push_back(c);
        if (delimeters.find(c) == end(delimeters))
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

std::vector<std::string> getPostFixExpression(const std::vector<std::string>& inFixExpression)
{
    typedef std::queue<std::string, std::deque<std::string>> Queue;
    
    std::stack<char> operatorStack;
    Queue outputQueue;
    Queue inFixQueue(std::deque<std::string>(begin(inFixExpression), end(inFixExpression)));
    
    /* This implementation does not implement composite functions,functions with variable number of arguments, and unary operators. */

    while (!inFixQueue.empty()) {
        const auto token = inFixQueue.front();
        inFixQueue.pop();
        if (std::all_of(begin(token), end(token), [](const char& c) { return std::isdigit(c); }))
            outputQueue.push(token);
        if (token.size() != 1)
            continue;
        const char tokenLetter = token.at(0);
        if (std::find_if(begin(operatorPrecedence), end(operatorPrecedence),
                         [&tokenLetter](const auto& pair) { return pair.first == tokenLetter; }) != end(operatorPrecedence))
        {
            if (!operatorStack.empty())
            {
                int tokenPrecendence = operatorPrecedence.at(tokenLetter);
                while (operatorStack.top() != '(' && operatorPrecedence.at(operatorStack.top()) >= tokenPrecendence) {
                    outputQueue.push(std::string(1, operatorStack.top()));
                    operatorStack.pop();
                }
            }
            operatorStack.push(tokenLetter);
            
        }
        if (tokenLetter == '(')
            operatorStack.push(tokenLetter);
        if (tokenLetter == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                outputQueue.push(std::string(1, operatorStack.top()));
                operatorStack.pop();
            }
            /* if the stack runs out without finding a left paren, then there are mismatched parentheses. */
            if (!operatorStack.empty() && operatorStack.top() == '(')
                operatorStack.pop();
        }
    }

    if (!operatorStack.empty()) {
        while (!operatorStack.empty()) {      
            outputQueue.push(std::string(1, operatorStack.top()));
            operatorStack.pop();
        }
    }
    
    std::vector<std::string> postFix;
    while (!outputQueue.empty())
    {
        postFix.push_back(outputQueue.front());
        outputQueue.pop();
    }
    return postFix;
}

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
    auto foo = tokenizeExpression(answer, delimeters());
    for (auto& item : getPostFixExpression(foo))
        std::cout << item << "\n";
    return 0;
}
