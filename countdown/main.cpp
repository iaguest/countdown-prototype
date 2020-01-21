//
//  main.cpp
//  countdown
//
//  Created by Ian Guest on 16/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <unordered_set>
#include <string>
#include <vector>

#include "io.h"
#include "timer.h"

std::vector<std::string> getSolutionWords1(const std::vector<std::string>& words, const std::string& lettersBoard)
{
    std::vector<std::string> solutionWords;
    for (auto wordIter = cbegin(words); wordIter != cend(words); ++wordIter)
    {
        const std::string& word = *wordIter;
        std::vector<char> availableLetters(begin(lettersBoard), end(lettersBoard));
        auto letterIter = cbegin(word);
        for (; letterIter != cend(word); ++letterIter)
        {
            auto foundIter = std::find(begin(availableLetters), end(availableLetters), *letterIter);
            if (foundIter == end(availableLetters))
                break;
            availableLetters.erase(foundIter);
        }
        if (letterIter == cend(word))
            solutionWords.push_back(*wordIter);
    }
    return solutionWords;
}

std::vector<std::string> getSolutionWords2(const std::vector<std::string>& words, const std::string& lettersBoard)
{
    std::vector<std::string> solutionWords;
    for (auto wordIter = cbegin(words); wordIter != cend(words); ++wordIter)
    {
        const std::string& word = *wordIter;
        bool isValid = true;
        for (const auto& letter: std::unordered_set<char>(begin(word), end(word)))
        {
            if (std::count(begin(word), end(word), letter) > std::count(begin(lettersBoard), end(lettersBoard), letter) )
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
            solutionWords.push_back(word);
    }
    return solutionWords;
}

std::vector<std::string> getSolutionWords3(const std::vector<std::string>& words, std::string lettersBoard)
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

int main(int argc, const char * argv[])
{

    const std::size_t lettersBoardSize = 9;
    const std::string path = "/Users/ianguest/C++/countdown/countdown";
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
    std::vector<std::string> solutionWords = getSolutionWords3(words, lettersBoard);
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
    
    return 0;
}
