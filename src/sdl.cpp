#include "utils.hpp"

bool loadMedia();

bool initSdl()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    TTF_Init();

    if (Mix_OpenAudio(audioFrequency, MIX_DEFAULT_FORMAT, hardwareChannels, audioChunkSize) < 0)
    {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    success = success ? loadMedia() : success;
    return success;
}
bool loadMedia()
{
    bool success = true;

    gWindow = SDL_CreateWindow("Starships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        cerr << "Error creating a window!" << endl;
        success = false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == nullptr)
    {
        cerr << "Error creating a render!" << endl;
        success = false;
    }

    gFont = TTF_OpenFont("../data/graphics/fonts/TiltNeon-Regular.ttf", 20);

    if (gFont == nullptr)
    {
        cerr << "Error creating a font!" << endl;
        success = false;
    }

    gMusic = Mix_LoadMUS("../data/music/07. Violet Sky - Infinity Space.mp3");

    if (gMusic == NULL)
    {
        cerr << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    gEngineSound = Mix_LoadWAV("../data/sound/engine_loop.wav");

    if (gEngineSound == NULL)
    {
        cerr << "Failed to load gEngineSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}
void cleanSdl()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_FreeChunk(gEngineSound);
    Mix_FreeMusic(gMusic);

    Mix_Quit();
    IMG_Quit();
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
