#pragma once
#include "rendering/menu_ui/button.hpp"
#include "utils.hpp"
#include "level.hpp"
#include "rendering/object.hpp"
#include "rendering/text.hpp"

namespace levels
{
  class Menu : public Level
  {
    int buttonW{200};
    int buttonH{50};
    int buttonY{(int)SCREEN_HEIGHT / 2 - 3 * buttonH / 2};
    int buttonX{(int)SCREEN_WIDTH / 2 - buttonW / 2};

    rendering::Button continueButton;
    rendering::Button newGameButton;
    rendering::Button quitButton;

    rendering::Text title;

    rendering::Object background{"../data/graphics/backgrounds/background3.jpg", {3000, 3000}, "background", 0.4};

  public:
    Menu();
    virtual ~Menu() {}
    virtual void handleEvent(SDL_Event &event, LevelType &levelType, bool &quit, bool &newGame) override;

  private:
    virtual void render() override;
  };

} // namespace levels