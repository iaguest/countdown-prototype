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


LettersGame::LettersGame(const std::string& resourcePath,
                         const std::vector<std::string>& words,
                         int numConsonants,
                         int numVowels)
  : AbstractGame(resourcePath),
    words(words),
    numConsonants(numConsonants),
    numVowels(numVowels)
{
}

void LettersGame::initialize()
{
    // TODO: Use correct number of consonants and vowels.
    
    std::vector<char> letters = Io::getLetters(path, letterDistributionFileName);
    assert (letters.size());
    
    std::shuffle(begin(letters), end(letters), gen);
    
    std::sample(begin(letters), end(letters), std::back_inserter(lettersBoard),
                Constants::lettersBoardSize, gen);
}

int LettersGame::getScore(const std::string& answer) const
{
    std::vector<std::string> solutionWords = getSolutionWords(words, lettersBoard);

    std::sort(begin(solutionWords), end(solutionWords));
    std::stable_sort(begin(solutionWords), end(solutionWords),
                     [](const auto& elem1, const auto elem2) { return elem1.size() < elem2.size(); });
    
    if (std::find(begin(solutionWords), end(solutionWords), answer) != end(solutionWords))
        return static_cast<int>(answer.size());
    
    return 0;
}

std::vector<std::string> LettersGame::getSolutionWords(const std::vector<std::string>& words,
                                                       std::vector<char> lettersBoard) const
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
