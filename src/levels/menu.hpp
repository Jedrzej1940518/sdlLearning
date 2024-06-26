#pragma once
#include "utils.hpp"
#include "level.hpp"

#include "rendering/button.hpp"
#include "rendering/background.hpp"
#include "rendering/object.hpp"

#include <SFML/Graphics/Font.hpp>

namespace levels
{
  class Menu : public Level
  {
    float buttonW{200};
    float buttonH{50};
    float buttonY{(float)config::SCREEN_HEIGHT / 2 - 3 * buttonH / 2};
    float buttonX{(float)config::SCREEN_WIDTH / 2 - buttonW / 2};

    rendering::Button newGameButton;
    rendering::Button continueButton;
    rendering::Button quitButton;
    sf::Font font;
    std::vector<rendering::Button *> buttons;

    rendering::Background background{prefabs::background};

  public:
    Menu(LevelType &level);
    virtual ~Menu() {}
    virtual void handleEvents(const sf::Event &event) override;

  private:
    virtual void render() override;
  };

} // namespace levels