//
//  LettersGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef LettersGame_h
#define LettersGame_h

#include <string>
#include <vector>

#include "AbstractGame.h"
#include "WordType.h"

class LettersGame : public AbstractGame<char>
{
public:
    explicit LettersGame(std::mt19937& gen,
                         const std::vector<char>& letters,
                         const std::vector<std::string>& words,
                         const std::vector<WordType>& choices);
    
    void initialize() override;
    
    int getScore(const std::string& answer) const override;

private:
    std::vector<std::string> getSolutionWords(const std::vector<std::string>& words,
                                              std::vector<char> lettersBoard) const;
private:
    std::vector<char> letters;
    const std::vector<std::string>& words;
    const std::size_t numConsonants;
    const std::size_t numVowels;
};

#endif /* LettersGame_h */
