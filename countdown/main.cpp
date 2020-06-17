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

#include "ConundrumGame.h"
#include "GameRunner.h"
#include "IGame.h"
#include "Io.h"
#include "LettersGame.h"
#include "NumbersGame.h"
#include "Timer.h"

#include "ExpressionsGenerator.h"
#include "PermutationsGenerator.h"
#include "SimpleExpressionsGenerator.h"

template <class T>
void printGenerator(std::ostream& os, IGenerator<T>& g) {
    for (g.first(); !g.isDone(); g.next()) {
        for (auto i: g.currentItem())
            os << i;
        os << std::endl;
    }
}

template <class T>
void printGenerator(IGenerator<T>& g)
{
    printGenerator(std::cout, g);
}

int main(int argc, const char * argv[])
{
    Timer t;
    ExpressionsGenerator foo(std::vector{1,2,3,4});
//    SubPermutationsGenerator foo(std::vector<int>{1,2,3,4,5,6}, 4);
//    printGenerator(std::cout, foo);
    int i = 0;
    do {
        foo.next();
        //simples.push_back(foo.currentItem());
        ++i;
    } while(!foo.isDone());    
    std::cout << i << std::endl;
    std::cout << "Elapsed time: " << t.elapsed() << std::endl;
    
//    std::mt19937 gen(std::random_device{}());
//    
//    const std::string resourcePath = "/Users/ianguest/C++/countdown/countdown/resources";
//    
//    std::vector<char> vowels = Io::getLetters(resourcePath, "vowels.txt");
//    std::vector<char> consonants = Io::getLetters(resourcePath, "consonants.txt");
//    std::vector<std::string> words = Io::getWords(resourcePath, "UK_english_truncated.txt");
//        
//    std::vector<IGame*> games;
//    LettersGame g1(gen, vowels, consonants, words);
//    NumbersGame g2(gen);
//    ConundrumGame g3(gen, words);
//    //games.push_back(&g1);
//    games.push_back(&g2);
//    //games.push_back(&g3);
//    GameRunner bob(games);
//    std::cout << bob.execute();
//    return 0;
}
