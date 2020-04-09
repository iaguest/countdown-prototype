//
//  SubPermutationsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 25/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef SubPermutationsGenerator_h
#define SubPermutationsGenerator_h

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_set>

#include "IGenerator.h"

// Return successive r-length permutations of elements in the sequence.
template <class T>
class SubPermutationsGenerator : public IGenerator<T>
{
public:
    SubPermutationsGenerator(const T& sequence, std::size_t r)
      : IGenerator<T>(), sequence(sequence), r(r)
    {
        assert (r <= sequence.size());
        reset();
    }
    
    void first() override { reset(); }
    
    void next() override {
        while (true) {
            hasNext = std::next_permutation(begin(sequence), end(sequence));
            const std::string sequenceStr = currentItemString();
            if (isDone() || seen.find(sequenceStr) == end(seen)) {
                seen.insert(sequenceStr);
                break;
            }
        }
    }
    
    bool isDone() const override { return !hasNext; }
    
    T currentItem() const override { return T(begin(sequence), begin(sequence) + r); }
    
private:
    void reset() {
        std::sort(begin(sequence), end(sequence));
        hasNext = sequence.size();
        seen.clear();
        seen.insert(currentItemString());
    }
    
    std::string currentItemString() const {
        std::ostringstream os;
        T seq = currentItem();
        for (const auto& item: seq)
            os << item;
        return os.str();
    }
    
private:
    T sequence;
    std::size_t r;
    bool hasNext;
    std::unordered_set<std::string> seen;
};

#endif /* SubPermutationsGenerator_h */
