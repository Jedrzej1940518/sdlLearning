#pragma once

#include "sdl.hpp"

class Clock
{
    uint frameRate;
    uint startTime{0};

  public:
    Clock(uint framesPerSecond) : frameRate{static_cast<uint>(1000. / framesPerSecond)}
    {
    }
    void tick()
    {
        startTime = SDL_GetTicks();
    }
    void tock()
    {
        uint elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < frameRate)
        {
            SDL_Delay(frameRate - elapsedTime);
        }
    }
};