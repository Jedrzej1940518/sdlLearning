#pragma once

#include "../physics/physics.hpp"
#include "word.hpp"
#include <vector>

namespace interpreter
{
    namespace physics
    {
        struct Vector2d;
    }

    class Line
    {
        std::vector<Word> words;

    public:
        Line();
        const auto &getWords() const { return words; }
        void push_back(char c);
        void pop_back();

        uint size() const;
    };
}