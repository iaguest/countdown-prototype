//
//  LettersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 11/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "../../catch/catch.hpp"

#include "../countdown/LettersGame.h"
#include "TestUtils.h"

#include <random>
#include <vector>

TEST_CASE("Validate LettersGame behavior.")
{
    // initialization
    std::mt19937 gen(1);
    std::ostringstream oss;
    std::istringstream iss;
    
    const std::vector<char> vowels{'a','e','i','o','u'};
    const std::vector<char> consonants{'p','s','t','c','h'};
    const std::vector<std::string> words{"cup", "peach", "push"};

    auto isVowel = [&vowels](char& c)
        { return std::find(begin(vowels), end(vowels), c) != end(vowels); };
    auto isConsonant = [&consonants](char& c)
        { return std::find(begin(consonants), end(consonants), c) != end(consonants); };
    
    SECTION("LettersGame construction success")
    {
        REQUIRE_NOTHROW(LettersGame(gen, vowels, consonants, words));
    }
    
    SECTION("Game board is initially empty.")
    {
        auto game = LettersGame(gen, vowels, consonants, words);
        REQUIRE(game.getGameBoard().empty());
    }
    
    SECTION("Game board is filled on initialize.")
    {
        auto game = LettersGame(gen, vowels, consonants, words);
        iss.str("c v c v c v c v c");
        
        game.initialize(oss, iss);
        
        REQUIRE_THAT("c u p e c a p e h", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("Game board has expected number of vowels and consonants after initialization.")
    {
        auto game = LettersGame(gen, vowels, consonants, words);
        iss.str("v c v c c c v c v");
        
        game.initialize(oss, iss);
        
        auto gameBoard = TestUtils::stringToVec<char>(game.getGameBoard());
        CHECK(4 == std::count_if(begin(gameBoard), end(gameBoard),
                                 [&isVowel](auto& elem) { return isVowel(elem); }));
        REQUIRE(5 == std::count_if(begin(gameBoard), end(gameBoard),
                                   [&isConsonant](auto& elem) { return isConsonant(elem); }));
    }
    
    SECTION("Score for a 'valid' answer equals number of letters in word")
    {
        auto game = LettersGame(gen, vowels, consonants, words);
        iss.str("c v c v c v c c c");        
        game.initialize(oss, iss);
        CHECK_THAT("c u p e c a p s h", Catch::Equals(game.getGameBoard()));
        
        CHECK(3 == game.getScore("cup"));
        CHECK(5 == game.getScore("peach"));
        REQUIRE(4 == game.getScore("push"));
    }
    
    SECTION("Score for an 'invalid' answer is zero")
    {
        auto game = LettersGame(gen, vowels, consonants, words);
        iss.str("c v c v c v c c c");        
        game.initialize(oss, iss);
        CHECK_THAT("c u p e c a p s h", Catch::Equals(game.getGameBoard()));
        
        CHECK(0 == game.getScore("paced"));  // letter missing from board
        CHECK(0 == game.getScore("shape"));  // valid letters but shape not in words list
        CHECK(0 == game.getScore("p each")); // valid word but with erroneous space
        CHECK(0 == game.getScore("g0bb*ldeGoo&k"));
        REQUIRE(0 == game.getScore(""));
    }
}
