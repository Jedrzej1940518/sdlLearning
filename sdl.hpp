
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

namespace sdl
{
    void initSdl();
    void cleanSdl();
    SDL_Texture *loadTexture(const string path);
}
