//
//  ConundrumGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 11/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "../../catch/catch.hpp"

#include "../countdown/ConundrumGame.h"
#include "TestUtils.h"

TEST_CASE("Validate ConundrumGame behavior.")
{
    // initialization
    std::mt19937 gen(1);
    std::ostringstream oss;
    std::istringstream iss;
    
    const std::vector<std::string> words{"parachute"};
    
    SECTION("ConundrumGame construction succeeds.")
    {
        REQUIRE_NOTHROW(ConundrumGame(gen, words));
    }
    
    SECTION("Game board initially empty.")
    {
        auto game = ConundrumGame(gen, words);
        REQUIRE(game.getGameBoard().empty());
    }
    
    SECTION("Game board is filled on initialize.")
    {
        auto game = ConundrumGame(gen, words);
        game.initialize(oss, iss);
        REQUIRE_THAT("h c u a p e t a r", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("Correct answer scores 10 points.")
    {
        auto game = ConundrumGame(gen, words);
        game.initialize(oss, iss);
        REQUIRE(10 == game.getScore("parachute"));
    }
    
    SECTION("Incorrect answer score 0 points.")
    {   auto game = ConundrumGame(gen, words);
        game.initialize(oss,iss);
        REQUIRE(0 == game.getScore("badger"));
    }
    
    SECTION("endMessage includes correct word.")
    {
        auto game = ConundrumGame(gen, words);
        game.initialize(oss, iss);
        REQUIRE(game.endMessage().find("parachute") != std::string::npos);
    }
}
