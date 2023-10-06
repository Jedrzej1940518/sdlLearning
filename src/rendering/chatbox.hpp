#pragma once

#include <array>
#include <boost/circular_buffer.hpp>
#include "../sdl.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/lines.hpp"

namespace rendering
{
  class Chatbox
  {
    static constexpr int maxLines{8};
    static constexpr int maxInstructions{8};
    static constexpr int xLinesMargin = 10;
    static constexpr int yLinesMargin = 10;

    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect dstrect;

    interpreter::Lines lines;

    boost::circular_buffer<string> instructions{maxInstructions};

    interpreter::Interpreter interpreter;

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