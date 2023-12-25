#pragma once
#include "../rendering/menu_ui/button.hpp"
#include "../utils.hpp"
#include "level.hpp"

namespace levels
{
  class Menu : public Level
  {
    rendering::Button newGameButton;
    rendering::Button quitButton;

  public:
    Menu();
    virtual void handleEvent(SDL_Event &event, LevelType &levelType, bool &quit) override;

  private:
    virtual void render() override;
  };

} // namespace levels