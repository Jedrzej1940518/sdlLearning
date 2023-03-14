#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"
#include "../object.hpp"
#include "level.hpp"

namespace levels
{
    class Arena: public Level
    {
        SDL_Texture *texture;
        SDL_Rect viewport;
        Object ship{"../data/graphics/ships/scarab.png", {500, 500}, {0,0}, Direction::NONE, 1, {5,5}};
        Object* controledObject{&ship};

    public:
        Arena();
        virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool& /**/) override;

    private:
        void moveViewport();
        virtual void render() override;
    };
}