#pragma once

#include "mySdl.hpp"
#include "utils.hpp"
#include <string>

using namespace std;

namespace rendering
{

  class Button
  {
    string text;
    SDL_Rect position;
    SDL_Color textColor{0, 0, 0, 0};
    SDL_Texture *texture;
    int textW;
    int textH;

  public:
    void renderButton();
    bool isInside(const SDL_Point &p);
    Button(string text, SDL_Rect position);
  };
} // namespace rendering