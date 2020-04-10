//
//  ExpressionsGeneratorTests.h
//  countdown
//
//  Created by Ian Guest on 09/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "../../catch/catch.hpp"

#include "../countdown/utilities/expression_generators/ExpressionsGenerator.h"

#include <algorithm>
#include <string>
#include <vector>

namespace ExpressionsGeneratorTest
{

static const std::vector<std::string> twoNumberCaseExpectedValues {
    "1", "2", "1+2", "1-2", "1*2", "1/2", "2+1", "2-1", "2*1", "2/1"
    
};

static const std::vector<std::string> threeNumberCaseExpectedValues { "1", "2", "3", "1+2", "1-2", "1*2", "1/2", "1+3", "1-3", "1*3", "1/3", "2+1", "2-1", "2*1", "2/1", "2+3", "2-3", "2*3", "2/3", "3+1", "3-1", "3*1", "3/1", "3+2", "3-2", "3*2", "3/2", "1+2+3", "1+2-3", "1+2*3", "1+2/3", "1-2+3", "1-2-3", "1-2*3", "1-2/3", "1*2+3", "1*2-3", "1*2*3", "1*2/3", "1/2+3", "1/2-3", "1/2*3", "1/2/3", "1+3+2", "1+3-2", "1+3*2", "1+3/2", "1-3+2", "1-3-2", "1-3*2", "1-3/2", "1*3+2", "1*3-2", "1*3*2", "1*3/2", "1/3+2", "1/3-2", "1/3*2", "1/3/2", "2+1+3", "2+1-3", "2+1*3", "2+1/3", "2-1+3", "2-1-3", "2-1*3", "2-1/3", "2*1+3", "2*1-3", "2*1*3", "2*1/3", "2/1+3", "2/1-3", "2/1*3", "2/1/3", "2+3+1", "2+3-1", "2+3*1", "2+3/1", "2-3+1", "2-3-1", "2-3*1", "2-3/1", "2*3+1", "2*3-1", "2*3*1", "2*3/1", "2/3+1", "2/3-1", "2/3*1", "2/3/1", "3+1+2", "3+1-2", "3+1*2", "3+1/2", "3-1+2", "3-1-2", "3-1*2", "3-1/2", "3*1+2", "3*1-2", "3*1*2", "3*1/2", "3/1+2", "3/1-2", "3/1*2", "3/1/2", "3+2+1", "3+2-1", "3+2*1", "3+2/1", "3-2+1", "3-2-1", "3-2*1", "3-2/1", "3*2+1", "3*2-1", "3*2*1", "3*2/1", "3/2+1", "3/2-1", "3/2*1", "3/2/1", "(1+2)", "(1-2)", "(1*2)", "(1/2)", "(1+3)", "(1-3)", "(1*3)", "(1/3)", "(2+1)", "(2-1)", "(2*1)", "(2/1)", "(2+3)", "(2-3)", "(2*3)", "(2/3)", "(3+1)", "(3-1)", "(3*1)", "(3/1)", "(3+2)", "(3-2)", "(3*2)", "(3/2)", "(1+2)+3", "(1+2+3)", "1+(2+3)", "(1+2)-3", "(1+2-3)", "1+(2-3)", "(1+2)*3", "(1+2*3)", "1+(2*3)", "(1+2)/3", "(1+2/3)", "1+(2/3)", "(1-2)+3", "(1-2+3)", "1-(2+3)", "(1-2)-3", "(1-2-3)", "1-(2-3)", "(1-2)*3", "(1-2*3)", "1-(2*3)", "(1-2)/3", "(1-2/3)", "1-(2/3)", "(1*2)+3", "(1*2+3)", "1*(2+3)", "(1*2)-3", "(1*2-3)", "1*(2-3)", "(1*2)*3", "(1*2*3)", "1*(2*3)", "(1*2)/3", "(1*2/3)", "1*(2/3)", "(1/2)+3", "(1/2+3)", "1/(2+3)", "(1/2)-3", "(1/2-3)", "1/(2-3)", "(1/2)*3", "(1/2*3)", "1/(2*3)", "(1/2)/3", "(1/2/3)", "1/(2/3)", "(1+3)+2", "(1+3+2)", "1+(3+2)", "(1+3)-2", "(1+3-2)", "1+(3-2)", "(1+3)*2", "(1+3*2)", "1+(3*2)", "(1+3)/2", "(1+3/2)", "1+(3/2)", "(1-3)+2", "(1-3+2)", "1-(3+2)", "(1-3)-2", "(1-3-2)", "1-(3-2)", "(1-3)*2", "(1-3*2)", "1-(3*2)", "(1-3)/2", "(1-3/2)", "1-(3/2)", "(1*3)+2", "(1*3+2)", "1*(3+2)", "(1*3)-2", "(1*3-2)", "1*(3-2)", "(1*3)*2", "(1*3*2)", "1*(3*2)", "(1*3)/2", "(1*3/2)", "1*(3/2)", "(1/3)+2", "(1/3+2)", "1/(3+2)", "(1/3)-2", "(1/3-2)", "1/(3-2)", "(1/3)*2", "(1/3*2)", "1/(3*2)", "(1/3)/2", "(1/3/2)", "1/(3/2)", "(2+1)+3", "(2+1+3)", "2+(1+3)", "(2+1)-3", "(2+1-3)", "2+(1-3)", "(2+1)*3", "(2+1*3)", "2+(1*3)", "(2+1)/3", "(2+1/3)", "2+(1/3)", "(2-1)+3", "(2-1+3)", "2-(1+3)", "(2-1)-3", "(2-1-3)", "2-(1-3)", "(2-1)*3", "(2-1*3)", "2-(1*3)", "(2-1)/3", "(2-1/3)", "2-(1/3)", "(2*1)+3", "(2*1+3)", "2*(1+3)", "(2*1)-3", "(2*1-3)", "2*(1-3)", "(2*1)*3", "(2*1*3)", "2*(1*3)", "(2*1)/3", "(2*1/3)", "2*(1/3)", "(2/1)+3", "(2/1+3)", "2/(1+3)", "(2/1)-3", "(2/1-3)", "2/(1-3)", "(2/1)*3", "(2/1*3)", "2/(1*3)", "(2/1)/3", "(2/1/3)", "2/(1/3)", "(2+3)+1", "(2+3+1)", "2+(3+1)", "(2+3)-1", "(2+3-1)", "2+(3-1)", "(2+3)*1", "(2+3*1)", "2+(3*1)", "(2+3)/1", "(2+3/1)", "2+(3/1)", "(2-3)+1", "(2-3+1)", "2-(3+1)", "(2-3)-1", "(2-3-1)", "2-(3-1)", "(2-3)*1", "(2-3*1)", "2-(3*1)", "(2-3)/1", "(2-3/1)", "2-(3/1)", "(2*3)+1", "(2*3+1)", "2*(3+1)", "(2*3)-1", "(2*3-1)", "2*(3-1)", "(2*3)*1", "(2*3*1)", "2*(3*1)", "(2*3)/1", "(2*3/1)", "2*(3/1)", "(2/3)+1", "(2/3+1)", "2/(3+1)", "(2/3)-1", "(2/3-1)", "2/(3-1)", "(2/3)*1", "(2/3*1)", "2/(3*1)", "(2/3)/1", "(2/3/1)", "2/(3/1)", "(3+1)+2", "(3+1+2)", "3+(1+2)", "(3+1)-2", "(3+1-2)", "3+(1-2)", "(3+1)*2", "(3+1*2)", "3+(1*2)", "(3+1)/2", "(3+1/2)", "3+(1/2)", "(3-1)+2", "(3-1+2)", "3-(1+2)", "(3-1)-2", "(3-1-2)", "3-(1-2)", "(3-1)*2", "(3-1*2)", "3-(1*2)", "(3-1)/2", "(3-1/2)", "3-(1/2)", "(3*1)+2", "(3*1+2)", "3*(1+2)", "(3*1)-2", "(3*1-2)", "3*(1-2)", "(3*1)*2", "(3*1*2)", "3*(1*2)", "(3*1)/2", "(3*1/2)", "3*(1/2)", "(3/1)+2", "(3/1+2)", "3/(1+2)", "(3/1)-2", "(3/1-2)", "3/(1-2)", "(3/1)*2", "(3/1*2)", "3/(1*2)", "(3/1)/2", "(3/1/2)", "3/(1/2)", "(3+2)+1", "(3+2+1)", "3+(2+1)", "(3+2)-1", "(3+2-1)", "3+(2-1)", "(3+2)*1", "(3+2*1)", "3+(2*1)", "(3+2)/1", "(3+2/1)", "3+(2/1)", "(3-2)+1", "(3-2+1)", "3-(2+1)", "(3-2)-1", "(3-2-1)", "3-(2-1)", "(3-2)*1", "(3-2*1)", "3-(2*1)", "(3-2)/1", "(3-2/1)", "3-(2/1)", "(3*2)+1", "(3*2+1)", "3*(2+1)", "(3*2)-1", "(3*2-1)", "3*(2-1)", "(3*2)*1", "(3*2*1)", "3*(2*1)", "(3*2)/1", "(3*2/1)", "3*(2/1)", "(3/2)+1", "(3/2+1)", "3/(2+1)", "(3/2)-1", "(3/2-1)", "3/(2-1)", "(3/2)*1", "(3/2*1)", "3/(2*1)", "(3/2)/1", "(3/2/1)", "3/(2/1)"
};

static const std::vector<std::string> fourNumberCaseExpectedValues = {
    "(2*1)+(4-3)", "4+(2+(1+3))", "4*(2/1)+3", "1*2*3*4", "1+(2*3)", "(4/(2*1))-3"
};

std::vector<std::string> toVector(ExpressionsGenerator& gen) {
    std::vector<std::string> output;
    for (gen.first(); !gen.isDone(); gen.next())
        output.push_back(gen.currentItem());
    return output;
}

template <class T>
bool containsSubset(const T& source, const T& target) {
    T source_copy(begin(source), end(source));
    T target_copy(begin(target), end(target));
    std::sort(begin(source_copy), end(source_copy));
    std::sort(begin(target_copy), end(target_copy));
    return std::includes(begin(source_copy), end(source_copy),
                         begin(target_copy), end(target_copy));
}

}

TEST_CASE("ExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ExpressionsGenerator(std::vector<int>{1,2,3}));
}

TEST_CASE("Validate expressions generated in two number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    SECTION("10 expressions are generated.") {
        REQUIRE(10 == output.size());
    }
    
    SECTION("Generated expressions contain expected values") {
        REQUIRE(ExpressionsGeneratorTest::containsSubset(
                    output, ExpressionsGeneratorTest::twoNumberCaseExpectedValues));
    }
}

TEST_CASE("Validate expressions generated in three number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    SECTION("435 expressions are generated.") {
        REQUIRE(435 == output.size());
    }
    
    SECTION("Contains expected permutations from two number case") {
        REQUIRE(ExpressionsGeneratorTest::containsSubset(
                    output, ExpressionsGeneratorTest::twoNumberCaseExpectedValues));
    }
    
    SECTION("Contains expected permutations for three number case") {
        REQUIRE(ExpressionsGeneratorTest::containsSubset(
                    output, ExpressionsGeneratorTest::threeNumberCaseExpectedValues));
    }
}

TEST_CASE("Four number case has N permutations") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3,4});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    SECTION("71188 expressions are generated.") {
        REQUIRE(71188 == output.size());
    }
    
    SECTION("Contains expected sample permutations") {
        REQUIRE(ExpressionsGeneratorTest::containsSubset(
                    output, ExpressionsGeneratorTest::fourNumberCaseExpectedValues));
    }
}
