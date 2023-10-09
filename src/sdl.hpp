
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

using namespace std;

bool initSdl();
void cleanSdl();
SDL_Texture *loadTexture(const string path);
