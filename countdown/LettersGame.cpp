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


LettersGame::LettersGame(std::mt19937& gen,
                         const std::vector<char>& vowels,
                         const std::vector<char>& consonants,
                         const std::vector<std::string>& words,
                         const std::vector<WordType>& choices)
  : AbstractGame(gen),
    vowels(vowels),
    consonants(consonants),
    words(words),
    numConsonants(std::count(begin(choices), end(choices), WordType::CONSONANT)),
    numVowels(std::count(begin(choices), end(choices), WordType::VOWEL))
{
}

void LettersGame::initialize()
{
    std::vector<char> letters(begin(vowels), end(vowels));
    std::copy(begin(consonants), end(consonants), std::back_inserter(letters));
    
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
