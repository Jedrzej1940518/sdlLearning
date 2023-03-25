#pragma once

#include "levels/arena.hpp"
#include "levels/level.hpp"
#include "levels/menu.hpp"
#include "sdl.hpp"
#include "utils.hpp"

class GameState
{
  LevelType levelType{LevelType::MENU};
  levels::Menu menu{};
  levels::Arena arena{};
  levels::Level *currentLevel{&menu};

public:
  void handleEvent(SDL_Event &event, bool &quit);
  void render();
};