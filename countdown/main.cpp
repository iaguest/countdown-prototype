//
//  main.cpp
//  countdown
//
//  Created by Ian Guest on 16/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>

#include <unordered_set>
#include <random>
#include <string>
#include <vector>

#include "Constants.h"
#include "GameRunner.h"
#include "Io.h"
#include "LettersGame.h"
#include "Timer.h"


int main(int argc, const char * argv[])
{
    const std::string path = "/Users/ianguest/C++/countdown/countdown";
    
    std::vector<std::string> words = Io::getWords(path, Constants::dictionaryWordsFileName);
    

//    static const int numbersBoardSize = 6;
//
//    std::random_device rd;  // used to seed random number engine
//    std::mt19937 gen(rd()); // random engine
//    std::array largeNumbers{ 25, 50, 75, 100 };
//    std::array smallNumbers{ 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 8 , 8 , 9 , 9 , 10 , 10 };
//    std::shuffle(begin(smallNumbers), end(smallNumbers), gen);
//
//    std::vector<int> numbersBoard;
//
//    std::size_t numLargeNumbers = std::uniform_int_distribution<>(0, largeNumbers.size())(gen);
//
//    std::sample(rbegin(largeNumbers), rend(largeNumbers), std::back_inserter(numbersBoard),
//                numLargeNumbers, std::mt19937{std::random_device{}()});
//    std::sample(smallNumbers.begin(), smallNumbers.end(), std::back_inserter(numbersBoard),
//                numbersBoardSize - numLargeNumbers, std::mt19937{std::random_device{}()});
//
//    for (auto i: numbersBoard) std::cout << i << std::endl;
//
//    wordGame(path);
    
    LettersGame g(path, words);
    GameRunner bob(g);
    std::cout << bob.execute();
    return 0;
}
