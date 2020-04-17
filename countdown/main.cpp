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


int main(int argc, const char * argv[])
{
    std::mt19937 gen(std::random_device{}());
    
    const std::string resourcePath = "/Users/ianguest/C++/countdown/countdown/resources";
    
    std::vector<char> vowels = Io::getLetters(resourcePath, "vowels.txt");
    std::vector<char> consonants = Io::getLetters(resourcePath, "consonants.txt");
    std::vector<std::string> words = Io::getWords(resourcePath, "UK_english_truncated.txt");
        
    std::vector<IGame*> games;
    LettersGame g1(gen, vowels, consonants, words);
    NumbersGame g2(gen);
    ConundrumGame g3(gen, words);
    //games.push_back(&g1);
    games.push_back(&g2);
    //games.push_back(&g3);
    GameRunner bob(games);
    std::cout << bob.execute();
    return 0;
}
