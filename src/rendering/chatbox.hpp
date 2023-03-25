#include "../sdl.hpp"
#include <array>
#include "../interpretter/interpretter.hpp"

namespace rendering
{
  class Chatbox
  {
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect dstrect;

    interpretter::Interpretter interpretter;

    SDL_Color textColor{255, 255, 0, 0};

    // int maxLines{2};
    int maxLineLenght{100};

    int textW;
    int textH;

    std::array<string, 2> lines;

    bool needToRender;

    void renderText();

  public:
    void render();
    void handleEvent(SDL_Event &event);
    void setControledObject(rendering::CollisionObject *ship);
    Chatbox(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect dstrect);
  };
} // namespace rendering