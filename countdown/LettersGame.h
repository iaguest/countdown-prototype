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

#include "IGame.h"

class LettersGame : public IGame<char>
{
public:
    LettersGame(const std::string& resourcePath,
                const std::vector<std::string>& words);
    
    std::vector<char> getGameBoard() const;
    
    bool allowInterrupts() const;
    
    int answerWaitTime() const;
    
    int calculateScore(const std::string& answer) const;

private:
    std::vector<std::string> getSolutionWords(const std::vector<std::string>& words,
                                              std::vector<char> lettersBoard) const;
private:
    static const std::string letterDistributionFileName;
    
    const std::string& path;
    const std::vector<std::string>& words;
    std::vector<char> lettersBoard;
};

#endif /* LettersGame_h */
