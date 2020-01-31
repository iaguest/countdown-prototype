//
//  NumbersGameUtils.hpp
//  countdown
//
//  Created by Ian Guest on 29/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef NumbersGameUtils_hpp
#define NumbersGameUtils_hpp

#include <deque>
#include <functional>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

namespace NumbersGameUtils
{

typedef std::queue<std::string, std::deque<std::string>> Queue;

const std::map<char, int>
    opPrecedence{ {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1} };

const std::map<char, std::function<double(double, double)>>
    opFunction{ {'*', std::multiplies<>()}, {'/', std::divides<>()}, {'+', std::plus<>()}, {'-', std::minus<>()} };

bool isOperator(const char& c)
{
    return std::find_if(begin(opPrecedence), end(opPrecedence),
                        [&c](const auto& p) { return p.first == c; }) != end(opPrecedence);
}

bool isNumber(const std::string& s)
{
    return std::all_of(begin(s), end(s), [](const char& c) { return std::isdigit(c); });
}

bool isLeftParen(const char& c) { return c == '('; }

bool isRightParen(const char& c) { return c == ')'; }

template <class T>
std::vector<T> toVector(const std::queue<T, std::deque<T>>& queue)
{
    std::queue<T, std::deque<T>> queueCopy = queue;
    std::vector<std::string> vec;
    while (!queueCopy.empty())
    {
        vec.push_back(queueCopy.front());
        queueCopy.pop();
    }
    return vec;
}

std::unordered_set<char> getDelimeters()
{
    std::unordered_set<char> delimeters{ '(', ')', ' ' };
    std::transform(begin(opPrecedence), end(opPrecedence), std::inserter(delimeters, end(delimeters)),
                   [](const auto& pair) { return pair.first; });
    return delimeters;
}

std::vector<std::string> tokenizeExpression(const std::string& expression) {
    std::unordered_set<char> delimeters = getDelimeters();
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
    std::stack<char> opStack;
    Queue outputQueue, inFixQueue(std::deque<std::string>(begin(inFixExpression), end(inFixExpression)));
    
    auto moveTopOperatorOnStackToOutputQueue = [&opStack, &outputQueue]()
    {
        outputQueue.push(std::string(1, opStack.top()));
        opStack.pop();
    };
    
    while (!inFixQueue.empty()) {        
        const auto token = inFixQueue.front();
        inFixQueue.pop();
        
        if (isNumber(token))
            outputQueue.push(token);      
        if (token.size() != 1)
            continue;
        
        const char tokenChar = token.front();
        if (isOperator(tokenChar))
        {
            int tokenPrecedence = opPrecedence.at(tokenChar);
            while (!opStack.empty() && !isLeftParen(opStack.top()) && opPrecedence.at(opStack.top()) >= tokenPrecedence)
                moveTopOperatorOnStackToOutputQueue();
            opStack.push(tokenChar);
        }
        else if (isLeftParen(tokenChar)) {
            opStack.push(tokenChar);
        }
        else if (isRightParen(tokenChar)) {
            while (!opStack.empty() && !isLeftParen(opStack.top()))
                moveTopOperatorOnStackToOutputQueue();
            if (!opStack.empty() && isLeftParen(opStack.top()))
                opStack.pop();
        }
    }
    
    if (!opStack.empty()) {
        while (!opStack.empty())    
            moveTopOperatorOnStackToOutputQueue();
    }    
    
    return toVector(outputQueue);
}

}

#endif /* NumbersGameUtils_hpp */
