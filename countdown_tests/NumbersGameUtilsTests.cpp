//
//  FirstCatchTest.cpp
//  countdown_tests
//
//  Created by Ian Guest on 29/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"

#include <iterator>
#include <string>
#include <vector>

#include "../countdown/NumbersGameUtils.hpp"

using namespace NumbersGameUtils;

TEST_CASE("tokenizeExpression splits simple expression into tokens.")
{    
    REQUIRE_THAT(std::vector<std::string>({ "(", "9", "+", "99", ")", "*", "(", "1", "-", "2", "/", "32", ")" }), 
                 Catch::Equals(tokenizeExpression("(9+99)*(1-2/32)")));
}

TEST_CASE("tokenizeExpression ignores spaces.")
{
    REQUIRE_THAT(std::vector<std::string>({ "(", "9", "+", "99", ")" }), 
                 Catch::Equals(tokenizeExpression(" ( 9 + 99) ")));
}

TEST_CASE("tokenizeExpression handles empty expression.")
{
    REQUIRE_NOTHROW(tokenizeExpression(""));
}

TEST_CASE("getPostFixExpression converts simple infix expression.")
{
    const std::vector<std::string>& result = getPostFixExpression(tokenizeExpression("3+4"));
    REQUIRE_THAT(std::vector<std::string>({"3","4","+"}), Catch::Equals(result));
}

TEST_CASE("getPostFixExpression converts more complicated infix expression.")
{
    const std::vector<std::string>& result = getPostFixExpression(tokenizeExpression("4+18/(9-3)"));
    
    REQUIRE_THAT(std::vector<std::string>({"4","18","9","3","-","/","+"}), Catch::Equals(result));
}

TEST_CASE("getPostFixExpression handles empty infix expression.")
{
    REQUIRE_NOTHROW(getPostFixExpression(std::vector<std::string>()));
}
