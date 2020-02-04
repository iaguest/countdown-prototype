//
//  LettersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <random>

#include "Constants.h"
#include "Io.h"
#include "LettersGame.h"

namespace
{
    const std::string letterDistributionFileName = "letter_distribution.txt";
}


LettersGame::LettersGame(const std::vector<char>& letters,
                         const std::vector<std::string>& words,
                         int numConsonants,
                         int numVowels)
  : AbstractGame(),
    letters(letters),
    words(words),
    numConsonants(numConsonants),
    numVowels(numVowels)
{
}

void LettersGame::initialize()
{
    std::shuffle(begin(letters), end(letters), gen);
    
    std::sample(begin(letters), end(letters), std::back_inserter(gameBoard),
                Constants::lettersBoardSize, gen);
}

int LettersGame::getScore(const std::string& answer) const
{
    std::vector<std::string> solutionWords = getSolutionWords(words, gameBoard);

    std::sort(begin(solutionWords), end(solutionWords));
    std::stable_sort(begin(solutionWords), end(solutionWords),
                     [](const auto& elem1, const auto elem2) { return elem1.size() < elem2.size(); });
    
    if (std::find(begin(solutionWords), end(solutionWords), answer) != end(solutionWords))
        return static_cast<int>(answer.size());
    
    return 0;
}

std::vector<std::string> LettersGame::getSolutionWords(const std::vector<std::string>& words,
                                                       std::vector<char> gameBoard) const
{
    std::vector<std::string> solutionWords;
    std::sort(begin(gameBoard), end(gameBoard));
    for (const auto& word: words)
    {
        std::string wordCopy = word;
        std::sort(begin(wordCopy), end(wordCopy));
        if (std::includes(begin(gameBoard), end(gameBoard), begin(wordCopy), end(wordCopy)))
            solutionWords.push_back(word);
    }
    return solutionWords;
}
