#pragma once

#include "levels/arena.hpp"
#include "levels/menu.hpp"
// #include "levels/gameOver.hpp"

// #include "utils.hpp"

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class GameState
{
  levels::LevelType levelType{levels::LevelType::MENU};

  levels::Menu menu;
  // levels::GameOver gameLost{"Game Over"};
  // levels::GameOver gameWon{"You win!"};
  levels::Arena *arena;
  levels::Level *currentLevel{&menu};

public:
  GameState() : menu{levelType}, arena{new levels::Arena(levelType)} {};
  void handleEvents();
  void render();
};