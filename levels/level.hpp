#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"

namespace levels
{
    class Level
    {
    public:
        virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool &quit) = 0;
        virtual void render() = 0;
    };
}