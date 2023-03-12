#pragma once

#include "utils.hpp"
#include "sdl.hpp"

namespace eventHandling
{

    void handleEvent(const SDL_Event &event, bool& quit);

}