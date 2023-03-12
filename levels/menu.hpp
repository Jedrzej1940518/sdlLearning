#pragma once

#include "../utils.hpp"
#include "../button.hpp"

namespace levels::menu
{
    class Menu
    {
        static Button newGameButton;
        static Button quitButton;

    public:
        void handleEvent(const SDL_Event &event, utils::Level &level, bool &quit);
        Menu(){}
    private:
        void renderMenu();
    };

}