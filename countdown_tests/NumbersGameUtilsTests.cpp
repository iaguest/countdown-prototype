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
    const std::string expressionString = "(9+99)";
    const std::vector<std::string> expected { "(", "9", "+", "99", ")" };
    
    const std::vector<std::string> result = NumbersGameUtils::tokenizeExpression(expressionString);
    
    REQUIRE_THAT(expected, Catch::Equals(result));
}
