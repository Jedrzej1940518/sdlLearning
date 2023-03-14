#pragma once

#include "sdl.hpp"
#include "levels/level.hpp"
#include "levels/menu.hpp"
#include "levels/arena.hpp"
#include "utils.hpp"

class GameState
{
    LevelType levelType{LevelType::MENU};
    levels::Menu menu{};
    levels::Arena arena{};
    levels::Level* currentLevel{&menu};

public:
    void handleEvent(const SDL_Event &event, bool &quit);
    void render();
};