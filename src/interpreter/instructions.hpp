
#pragma once

#include <set>
#include <string>
#include "../sdl.hpp"
// todo this all should be in a config profile per SAVE lol maybe in 20 years ;D
using namespace std;

namespace interpreter
{
    inline const set<string> INSTRUCTION_LIST{string{"rotate"}, string{"engage"}, string{"disengage"}, string{"stop"}};
    inline const string LINE_START{"Jedrzej$ "};

    namespace colors
    {
        inline const SDL_Color DEFAULT{255, 255, 255, 255};   // white
        inline const SDL_Color INSTRUCTION{0, 255, 0, 255};   // green
        inline const SDL_Color START_OF_LINE{0, 0, 255, 255}; // blue
    }
}