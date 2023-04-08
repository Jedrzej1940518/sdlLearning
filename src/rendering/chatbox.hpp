#pragma once

#include <array>
#include <boost/circular_buffer.hpp>
#include "../sdl.hpp"
#include "../interpretter/interpretter.hpp"

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
    boost::circular_buffer<string> lines{maxLines};
    boost::circular_buffer<string> instructions{maxInstructions};

    interpretter::Interpretter interpretter;

    string start{"Jedrzej$ "};

    int textH{0};
    SDL_Color textColor{0, 255, 0, 0};

    size_t maxLineLenght{40}; // todo calculate it?

    bool listed{false};

    void renderText();
    void renderLine(const string &s, int i);

    void handleCompositionChange();
    void listAllInstructions();
    void initTextSize();

    boost::circular_buffer<string>
    matchInstructions(const string &beggining);

  public:
    void render();
    void handleEvent(SDL_Event &event);
    void setControledObject(rendering::CollisionObject *ship);
    Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect);
    ~Chatbox();
  };
} // namespace rendering