#pragma once
#include "level.hpp"
#include "../utils.hpp"
#include "../button.hpp"

namespace levels
{
    class Menu: public Level
    {
        Button newGameButton;
        Button quitButton;

    public:
        Menu();
        virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool &quit) override;

    private:
        virtual void render() override;
    };

}