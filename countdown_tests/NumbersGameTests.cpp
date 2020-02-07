//
//  NumbersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 07/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "../../catch/catch.hpp"

#include "../countdown/NumbersGame.h"

TEST_CASE("NumbersGame construction succeeds.")
{
    NumbersGame(1, 1);
}
