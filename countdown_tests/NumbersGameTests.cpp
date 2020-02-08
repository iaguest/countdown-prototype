//
//  NumbersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 07/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <random>

#include "../../catch/catch.hpp"

#include "../countdown/NumbersGame.h"

TEST_CASE("Validate NumbersGame behavior.")
{
    // initialization
    std::mt19937 gen(1);
    
    SECTION("NumbersGame construction succeeds.")
    {
        REQUIRE_NOTHROW(NumbersGame(gen, 1));
    }

    SECTION("Game board initially empty.")
    {
        auto game = NumbersGame(gen, 1);
        REQUIRE(game.getGameBoard().empty());
    }

    SECTION("Game board filled on initialize.")
    {
        auto game = NumbersGame(gen, 1);
        game.initialize(); 
        REQUIRE_THAT("100 75 10 9 4 8", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("getTarget throws if uninitialized game")
    {
        auto game = NumbersGame(gen, 1);
        REQUIRE_THROWS(game.getTarget());
    }
    
    SECTION("getTarget returns game target value")
    {
        auto game = NumbersGame(gen, 1);
        game.initialize();
        REQUIRE(416 == game.getTarget());
    }
}
