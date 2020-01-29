//
//  FirstCatchTest.cpp
//  countdown_tests
//
//  Created by Ian Guest on 29/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"

#include <string>
#include <vector>

#include "../countdown/NumbersGameUtils.hpp"


TEST_CASE("tokenizeExpression splits simple expression into tokens.")
{    
    REQUIRE_THAT(std::vector<std::string>({ "(", "9", "+", "99", ")", "*", "(", "1", "-", "2", "/", "32", ")" }), 
                 Catch::Equals(NumbersGameUtils::tokenizeExpression(std::string("(9+99)*(1-2/32)"))));
}

TEST_CASE("tokenizeExpression ignores spaces.")
{
    REQUIRE_THAT(std::vector<std::string>({ "(", "9", "+", "99", ")" }), 
                 Catch::Equals(NumbersGameUtils::tokenizeExpression(std::string(" ( 9 + 99) "))));
}
