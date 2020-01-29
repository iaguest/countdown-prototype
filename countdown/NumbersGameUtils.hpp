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
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

namespace NumbersGameUtils
{

typedef std::queue<std::string, std::deque<std::string>> Queue;

const std::map<char, int> operatorPrecedence{ {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1} };

bool isOperator(const char& c)
{
    return std::find_if(begin(operatorPrecedence), end(operatorPrecedence),
                        [&c](const auto& p) { return p.first == c; }) != end(operatorPrecedence);
}

bool isNumber(const std::string& s)
{
    return std::all_of(begin(s), end(s), [](const char& c) { return std::isdigit(c); });
}

bool isLeftParenthesis(const char& c) { return c == '('; }

bool isRightParenthesis(const char& c) { return c == ')'; }

template <class T>
std::vector<T> makeQueue(const std::queue<T, std::deque<T>>& queue)
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

inline std::unordered_set<char> getDelimeters()
{
    std::unordered_set<char> delimeters{ '(', ')', ' ' };
    std::transform(begin(operatorPrecedence), end(operatorPrecedence), std::inserter(delimeters, end(delimeters)),
                   [](const auto& pair) { return pair.first; });
    return delimeters;
}

inline std::vector<std::string> tokenizeExpression(const std::string& expression) {
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

inline std::vector<std::string> getPostFixExpression(const std::vector<std::string>& inFixExpression)
{
    std::stack<char> operatorStack;
    Queue outputQueue, inFixQueue(std::deque<std::string>(begin(inFixExpression), end(inFixExpression)));
    
    while (!inFixQueue.empty()) {
        const auto token = inFixQueue.front();
        inFixQueue.pop();
        
        if (isNumber(token))
            outputQueue.push(token);
        
        if (token.size() != 1)
            continue;
        
        const char tokenChar = token.at(0);
        if (isOperator(tokenChar))
        {
            int tokenPrecedence = operatorPrecedence.at(tokenChar);
            while (!operatorStack.empty() && !isLeftParenthesis(operatorStack.top()) && operatorPrecedence.at(operatorStack.top()) >= tokenPrecedence) {
                outputQueue.push(std::string(1, operatorStack.top()));
                operatorStack.pop();
            }
            operatorStack.push(tokenChar);
            
        }
        else if (isLeftParenthesis(tokenChar)) {
            operatorStack.push(tokenChar);
        }
        else if (isRightParenthesis(tokenChar)) {
            while (!operatorStack.empty() && !isLeftParenthesis(operatorStack.top())) {
                outputQueue.push(std::string(1, operatorStack.top()));
                operatorStack.pop();
            }
            if (!operatorStack.empty() && isLeftParenthesis(operatorStack.top()))
                operatorStack.pop();
        }
    }

    if (!operatorStack.empty()) {
        while (!operatorStack.empty()) {      
            outputQueue.push(std::string(1, operatorStack.top()));
            operatorStack.pop();
        }
    }
    
    return makeQueue(outputQueue);
}

}

#endif /* NumbersGameUtils_hpp */
