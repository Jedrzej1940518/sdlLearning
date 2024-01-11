#include "soundManager.hpp"
#include "utils.hpp"

SoundManager::SoundManager()
{
    initAudio();
    loadData();

    // reserving channel 0 for engine
    Mix_ReserveChannels(1);

    printf("sound channels %d\n", Mix_AllocateChannels(32));
    Mix_Volume(-1, 20);
}
SoundManager::~SoundManager()
{
    Mix_FreeChunk(engineSound);
    Mix_FreeChunk(playerWeaponSound);
    Mix_FreeMusic(music);

    Mix_Quit();
}

SoundManager &SoundManager::GetInstance()
{
    static SoundManager soundManager;
    return soundManager;
}

void SoundManager::playMusic()
{
    if (not Mix_PlayingMusic())
    {
        Mix_FadeInMusic(music, -1, fadeMs);
    }
    else if (Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
}
void SoundManager::pauseMusic()
{
    if (not Mix_PausedMusic())
    {
        Mix_FadeOutMusic(fadeMs);
    }
}

void SoundManager::playSound(Sound sound)
{
    constexpr int engineChannel = 0;

    // for engine we dont want to play it if it was already playing
    if (sound == Sound::ENGINE && Mix_Playing(engineChannel))
        return;

    int channel = sound == Sound::ENGINE ? engineChannel : -1;
    auto res = Mix_PlayChannel(channel, chunkPtr[sound], 0);

    if (res == -1)
    {
        cerr << "Unable to play on channel " << channel << " for " << static_cast<int>(sound) << " " << Mix_GetError() << endl;
    }
}

bool SoundManager::initAudio()
{
    bool success = true;
    if (Mix_OpenAudio(audioFrequency, MIX_DEFAULT_FORMAT, hardwareChannels, audioChunkSize) < 0)
    {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    return success;
}

bool SoundManager::loadData()
{
    bool success = true;
    music = Mix_LoadMUS("../data/music/07. Violet Sky - Infinity Space.mp3");

    if (music == nullptr)
    {
        cerr << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    engineSound = Mix_LoadWAV("../data/sound/engine_03_hitek_01_frigate.ogg");

    if (engineSound == nullptr)
    {
        cerr << "Failed to load gEngineSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    playerWeaponSound = Mix_LoadWAV("../data/sound/hephaestus_fire_01.ogg");

    if (playerWeaponSound == nullptr)
    {
        cerr << "Failed to load playerWeaponSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    shellHitSmallSound = Mix_LoadWAV("../data/sound/gun_hit_light_01.ogg");

    if (shellHitSmallSound == nullptr)
    {
        cerr << "Failed to load shellHitSmallSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    shellHitBigSound = Mix_LoadWAV("../data/sound/gun_hit_heavy_03.ogg");

    if (shellHitBigSound == nullptr)
    {
        cerr << "Failed to load shellHitBigSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    collisionSound = Mix_LoadWAV("../data/sound/collision_asteroid_vs_asteroid_01.ogg");

    if (collisionSound == nullptr)
    {
        cerr << "Failed to load collisionSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // shellHitBigSound=

    chunkPtr[Sound::PLAYER_WEAPON] = playerWeaponSound;
    chunkPtr[Sound::ENGINE] = engineSound;
    chunkPtr[Sound::SHELL_HIT_SMALL] = shellHitSmallSound;
    chunkPtr[Sound::SHELL_HIT_BIG] = shellHitBigSound;
    chunkPtr[Sound::COLLISION] = collisionSound;

    return success;
}