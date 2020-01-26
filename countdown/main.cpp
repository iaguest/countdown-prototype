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
#include "ConundrumGame.h"
#include "GameRunner.h"
#include "IGame.h"
#include "Io.h"
#include "LettersGame.h"
#include "NumbersGame.h"
#include "Timer.h"


int main(int argc, const char * argv[])
{
    const std::string path = "/Users/ianguest/C++/countdown/countdown";
    
    std::vector<std::string> words = Io::getWords(path, Constants::dictionaryWordsFileName);
        
    std::vector<IGame*> games;
    ConundrumGame g1(path, words);
    LettersGame g2(path, words, 0, 0);
    NumbersGame g3(path, 0, 0);
    games.push_back(&g1);
    games.push_back(&g2);
    games.push_back(&g3);
    GameRunner bob(games);
    std::cout << bob.execute();
    return 0;
}
