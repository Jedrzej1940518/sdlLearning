#include "../sdl.hpp"
#include <array>
#include "../interpretter/interpretter.hpp"
#include "../carousel.hpp"

namespace rendering
{
  class Chatbox
  {
    static constexpr int maxLines{8};
    static constexpr int maxInstructions{8};

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect dstrect;
    SDL_Rect linesRect;
    Carousel<string, maxLines> lines;
    Carousel<string, maxInstructions> instructions;

    interpretter::Interpretter interpretter;

    string start{"Jedrzej$ "};
    string current{""};

    int textH{0};
    SDL_Color textColor{0, 255, 0, 0};

    size_t maxLineLenght{40}; // todo calculate it?

    bool listed{false};

    void renderText();
    void renderLine(const string &s, int i);

    void handleCompositionChange();
    void listAllInstructions();
    void initTextSize();

    Carousel<string, maxInstructions>
    matchInstructions(const string &beggining);

  public:
    void render();
    void handleEvent(SDL_Event &event);
    void setControledObject(rendering::CollisionObject *ship);
    Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect);
    ~Chatbox();
  };
} // namespace rendering