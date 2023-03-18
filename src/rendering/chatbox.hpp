#include "../sdl.hpp"

namespace rendering
{
class Chatbox
{
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Rect dstrect;

    int maxLines{20};
    int maxLineLenght{100};

    int textW;
    int textH;

    string lines[maxLines];

  public:
    void render();
    Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect);
};
} // namespace rendering