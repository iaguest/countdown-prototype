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

const std::map<char, int> operatorPrecedence{ {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1} };

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
            int tokenPrecendence = operatorPrecedence.at(tokenLetter);
            while (!operatorStack.empty() && operatorStack.top() != '(' && operatorPrecedence.at(operatorStack.top()) >= tokenPrecendence) {
                outputQueue.push(std::string(1, operatorStack.top()));
                operatorStack.pop();
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

}

#endif /* NumbersGameUtils_hpp */
