
#include "levels/menu.hpp"
#include "levels/arena.hpp"

using namespace utils;

namespace eventHandling
{

    void handleEvent(const SDL_Event &event, bool &quit)
    {
        static Level level = Level::MENU;
        static levels::menu::Menu menu{};
        static levels::arena::Arena arena{};

        switch (level)
        {
        case Level::MENU:
            menu.handleEvent(event, level, quit);
            break;
        case Level::ARENA:
            arena.handleEvent(event, level);
            break;
        }
    }
}