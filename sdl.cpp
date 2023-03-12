#include "utils.hpp"

using namespace utils;

namespace sdl
{
    void initSdl()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        gWindow = SDL_CreateWindow("Starships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        TTF_Init();

        gFont = TTF_OpenFont("data/TiltNeon-Regular.ttf", 20);
    }
    void cleanSdl()
    {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
    SDL_Texture *loadTexture(const string path)
    {
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());
        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        return newTexture;
    }
}