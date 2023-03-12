#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"

using namespace utils;

namespace levels::arena
{
    class Arena
    {
        SDL_Texture *texture;

    public:
        Arena();
        void handleEvent(const SDL_Event &event, Level &level);

    private:
        void renderArena();
    };
}