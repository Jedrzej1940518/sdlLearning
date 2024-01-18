#pragma once
#include "rendering/menu_ui/button.hpp"
#include "utils.hpp"
#include "level.hpp"
#include "rendering/object.hpp"
#include "rendering/text.hpp"

namespace levels
{
    class GameOver : public Level
    {
        int buttonW{200};
        int buttonH{50};
        int buttonY{(int)SCREEN_HEIGHT / 2 - 3 * buttonH / 2};
        int buttonX{(int)SCREEN_WIDTH / 2 - buttonW / 2};

        rendering::Object background{getDataPath("graphics/backgrounds/background3.jpg").c_str(), {3000, 3000}, "background", 0.4};

        rendering::Text text;
        rendering::Button playAgainButton;
        rendering::Button quitButton;

    public:
        GameOver(string &&title);
        virtual ~GameOver() {}
        virtual void handleEvents(SDL_Event &event, LevelType &levelType, bool &quit, bool &newGame) override;

    private:
        virtual void render() override;
    };

} // namespace levels