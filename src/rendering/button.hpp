#pragma once

#include "utils.hpp"
#include <string>
#include <functional>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace rendering
{

  class Button : public sf::RectangleShape
  {
  public:
    typedef std::function<void()> CallbackFunction;

  protected:
    CallbackFunction callback;
    sf::Text text;
    bool isInside(int x, int y);
    void click();

  public:
    Button();
    sf::Text &getText();
    void setCallback(CallbackFunction callbackFunction);
    bool handleClick(const sf::Event::MouseButtonEvent &mouseButton);
  };
} // namespace rendering