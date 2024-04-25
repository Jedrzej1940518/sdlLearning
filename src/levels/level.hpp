#pragma once

#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "rendering/button.hpp"

namespace levels
{

  enum class LevelType
  {
    MENU,
    ARENA,
    GAME_OVER,
    GAME_WON
  };

  class Level
  {
  protected:
    sf::RenderWindow &window;
    LevelType &level;

  public:
    Level(sf::RenderWindow &window, LevelType &level) : window{window}, level{level} {}
    virtual void handleEvents(const sf::Event &event) = 0;
    virtual void render() = 0;
    virtual ~Level(){};
  };
} // namespace levels