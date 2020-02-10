//
//  NumbersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 07/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <random>
#include <sstream>

#include "../../catch/catch.hpp"

#include "../countdown/NumbersGame.h"

TEST_CASE("Validate NumbersGame behavior.")
{
    // initialization
    std::mt19937 gen(1);
    std::ostringstream oss;
    std::istringstream iss;
    
    SECTION("NumbersGame construction succeeds.")
    {
        REQUIRE_NOTHROW(NumbersGame(gen));
    }

    SECTION("Game board initially empty.")
    {
        auto game = NumbersGame(gen);
        REQUIRE(game.getGameBoard().empty());
    }

    SECTION("Game board filled on initialize.")
    {
        auto game = NumbersGame(gen);
        iss.str("2");
        game.initialize(oss, iss); 
        REQUIRE_THAT("100 50 7 1 3 9", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("getTarget throws if uninitialized game")
    {
        auto game = NumbersGame(gen);
        REQUIRE_THROWS(game.getTarget());
    }
    
    SECTION("getTarget returns game target value")
    {
        auto game = NumbersGame(gen);
        game.initialize(oss, iss);
        REQUIRE(137 == game.getTarget());
    }
}
