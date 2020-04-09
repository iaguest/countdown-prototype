//
//  SimpleExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 26/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef SimpleExpressionsGenerator_h
#define SimpleExpressionsGenerator_h

#include <iterator>
#include <sstream>
#include <vector>

#include "PermutationsGenerator.h"

class SimpleExpressionsGenerator : public IGenerator<std::string>
{
public:
    SimpleExpressionsGenerator(const std::vector<int>& numberSequence)
      : IGenerator::IGenerator(),
        numGen(NumberSequenceGenerator(numberSequence)),
        opGen(makeOperatorSequenceGenerator(0))
    {
        reset();
    }
    
    void first() override {
        reset();
    }
    
    void next() override {
        opGen.next();
        if (opGen.isDone() && !numGen.isDone()) {
            numGen.next();
            opGen = makeOperatorSequenceGenerator(numGen.currentItem().size() - 1);
            return;
        }
    }
    
    bool isDone() const override {
        return numGen.isDone();
    }
    
    std::string currentItem() const override {
        std::ostringstream os;
        const auto& numSeq = numGen.currentItem();
        const auto& opSeq = opGen.currentItem();
        for (auto i = 0; i != opSeq.size(); ++i)
            os << numSeq.at(i) << opSeq.at(i);
        os << numSeq.back();
        return os.str();
    }

private:
    typedef PermutationsGenerator<std::vector<int>> NumberSequenceGenerator;
    typedef SubPermutationsGenerator<std::vector<char>> OperatorSequenceGenerator;
    
private:
    void reset() {
        numGen.first();
        opGen.first();
        expressions.clear();
    }

    OperatorSequenceGenerator makeOperatorSequenceGenerator(const std::size_t numOps) const
    {
        std::vector<char> ops;
        for (const auto& c: std::string("+-*/"))
            std::generate_n(std::back_inserter(ops), numOps, [&c](){ return c; });
        return OperatorSequenceGenerator(ops, numOps);
    }
    
    std::vector<std::string> makeTokens(const std::vector<int>& numSeq) const
    {
        std::vector<std::string> tokens;
        for (const auto& item: numSeq) {
            tokens.push_back(std::string());
            tokens.push_back(std::to_string(item));
        }
        tokens.push_back(std::string());
        return tokens;
    }    
    
private:
    NumberSequenceGenerator numGen;
    OperatorSequenceGenerator opGen;
    std::vector<std::vector<std::string>> expressions;
};

#endif /* SimpleExpressionsGenerator_h */
