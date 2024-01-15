#pragma once

#include "levels/arena.hpp"
#include "levels/level.hpp"
#include "levels/menu.hpp"
#include "levels/gameOver.hpp"
#include "mySdl.hpp"
#include "utils.hpp"

class GameState
{
  LevelType levelType{LevelType::MENU};
  levels::Menu menu{};
  levels::GameOver gameLost{"Game Over"};
  levels::GameOver gameWon{"You win!"};
  levels::Arena *arena{new levels ::Arena()};
  levels::Level *currentLevel{&menu};

public:
  void handleEvent(SDL_Event &event, bool &quit, bool &newGame);
  void render();
};