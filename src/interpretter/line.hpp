#pragma once

#include "../physics/physics.hpp"
#include "word.hpp"

namespace interpretter
{
    namespace physics
    {
        struct Vector2d;
    }

    class Line
    {
        constexpr uint maxWords{20}; // todo calculate this?
        std::vector<Word> words{{}}; // starts with one empty word

    public:
        Line() {}
        auto &getWords() { return words; }
        void push_back(char c);
        void pop();
    };
}