//
//  ExpressionsGeneratorTests.h
//  countdown
//
//  Created by Ian Guest on 09/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "../../catch/catch.hpp"

#include "../countdown/utilities/expression_generators/ExpressionsGenerator.h"


TEST_CASE("ExpressionsGenerator is constructable")
{
    REQUIRE_NOTHROW(ExpressionsGenerator(std::vector<int>{1,2,3}));
}
