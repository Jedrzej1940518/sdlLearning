
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>


bool initSdl();
void cleanSdl();
SDL_Texture *loadTexture(const std::string path);
