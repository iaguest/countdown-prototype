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


const std::string LettersGame::letterDistributionFileName = "letter_distribution.txt";

LettersGame::LettersGame(const std::string& resourcePath,
                         const std::vector<std::string>& words)
  : path(resourcePath), words(words)
{
    std::vector<char> letters = Io::getLetters(path, letterDistributionFileName);
    assert (letters.size());

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    std::shuffle(begin(letters), end(letters), gen);
    
    std::sample(begin(letters), end(letters), std::back_inserter(lettersBoard),
                Constants::lettersBoardSize, gen);
}

std::vector<char> LettersGame::getGameBoard() const
{
    return lettersBoard;
}

bool LettersGame::allowInterrupts() const
{
    return false;
}

int LettersGame::answerWaitTime() const
{
    return 10;
}

int LettersGame::calculateScore(const std::string& answer) const
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
