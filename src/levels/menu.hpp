#pragma once
#include "../rendering/button.hpp"
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
    virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool &quit) override;

  private:
    virtual void render() override;
};

} // namespace levels