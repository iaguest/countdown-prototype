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
#include <random>
#include <unordered_set>
#include <string>
#include <vector>

#include "io.h"
#include "timer.h"

std::vector<std::string> getSolutionWords(const std::vector<std::string>& words, std::string lettersBoard)
{
    std::vector<std::string> solutionWords;
    std::sort(begin(lettersBoard), end(lettersBoard));
    for (const auto& word: words)
    {
        std::string wordCopy = word;
        std::sort(begin(wordCopy), end(wordCopy));
        if (std::includes(begin(lettersBoard), end(lettersBoard), begin(wordCopy), end(wordCopy)))
            solutionWords.push_back(word);
    }
    return solutionWords;
}

void wordGame(const std::string& path)
{
    const std::size_t lettersBoardSize = 9;
    const std::string letters = io::getLetters(path, "letter_distribution.txt");
    assert (letters.size());

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    std::vector<std::string> words = io::getWords(path, "UK_english_truncated.txt");
    std::shuffle(begin(words), end(words), gen);
    
    const int lettersSize = static_cast<int>(letters.size());
    std::uniform_int_distribution<> dis(0, lettersSize - 1);
    
    std::string lettersBoard;
    std::generate_n(std::back_inserter(lettersBoard), lettersBoardSize, [&](){ return letters[dis(gen)]; });
    std::cout << lettersBoard << std::endl << std::endl;
    
    std::string guess;
    std::cout << "Enter guess: ";
    std::cin >> guess;
    
    Timer t;
    std::vector<std::string> solutionWords = getSolutionWords(words, lettersBoard);
    std::cout << t.elapsed() << std::endl;
    
    std::sort(begin(solutionWords), end(solutionWords));
    std::stable_sort(begin(solutionWords), end(solutionWords),
                     [](const auto& elem1, const auto elem2) { return elem1.size() < elem2.size(); });
    for (auto s: solutionWords)
        std::cout << s << std::endl;
    
    std::cout << std::endl;
    if (std::find(begin(solutionWords), end(solutionWords), guess) != end(solutionWords))
        std::cout << "Well done!" << std::endl;
    else
        std::cout << "Lame!" << std::endl;
}

int main(int argc, const char * argv[])
{
    const std::string path = "/Users/ianguest/C++/countdown/countdown";

    static const std::array largeNumbers{ 25, 50, 75, 100 };
    static const std::array smallNumbers{ 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 8 , 8 , 9 , 9 , 10 , 10 };
    
    
    return 0;
}
