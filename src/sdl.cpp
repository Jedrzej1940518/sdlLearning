#include "utils.hpp"

void initSdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("Starships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();

    gFont = TTF_OpenFont("../data/graphics/fonts/TiltNeon-Regular.ttf", 20);
    if(!gFont)
        cerr<<"Error opening font!"<<endl;
}
void cleanSdl()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
SDL_Texture *loadTexture(const string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        cerr << "Error loading img! " << path << " " << IMG_GetError() << endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (!texture)
    {
        cerr << "Error creating texture from surface! " << SDL_GetError() << endl;
    }
    SDL_FreeSurface(surface);

    return texture;
}
