//
//  io.h
//  countdown
//
//  Created by Ian Guest on 16/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef io_h
#define io_h

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

namespace io {

std::string makeFilePath(const std::string& path, const std::string& fileName)
{
    return path + "/" + fileName;
}

std::string getLetters(const std::string& path, const std::string& fileName)
{
    const std::string letterDistributionPath = makeFilePath(path, fileName);
    std::string letters;
    std::ifstream is(letterDistributionPath);
    if (is.is_open())
    {
        std::string line;
        while (std::getline(is, line))
        {
            if (line.empty())
                continue;
            const char letter = line[0];
            if (letter == '#')
                continue;
            auto sepIt = std::find(begin(line), end(line), ',');
            const int numLetters = std::stoi(std::string(++sepIt, end(line)));
            letters.append(numLetters, std::tolower(letter));
        }
    }
    return letters;
}

std::vector<std::string> getWords(const std::string& path, const std::string& fileName)
{
    const std::string wordsPath = makeFilePath(path, fileName);
    std::vector<std::string> words;
    std::ifstream is(wordsPath);
    if (is.is_open())
    {
        std::string line;
        while (std::getline(is, line))
            words.push_back(line);
    }
    return words;
}

}

#endif /* io_h */
