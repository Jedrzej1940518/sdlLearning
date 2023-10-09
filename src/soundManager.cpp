#include "soundManager.hpp"
#include "utils.hpp"

SoundManager::SoundManager()
{
    initAudio();
    loadData();
    Mix_Volume(-1, 20);
}
SoundManager::~SoundManager()
{
    Mix_FreeChunk(engineSound);
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
    bool musicNotPlaying = soundChannel.count(sound) == 0 or soundChannel[sound] == -1;

    if (musicNotPlaying)
    {
        soundChannel[sound] = Mix_FadeInChannel(-1, engineSound, -1, fadeMs);
    }
    if (soundChannel[sound] == -1)
    {
        cerr << "Unable to find channel for " << static_cast<int>(sound) << endl;
    }
}
void SoundManager::pauseSound(Sound sound)
{
    if (Mix_FadeOutChannel(soundChannel[sound], fadeMs) == -1)
    {
        cerr << "Error halting channel " << static_cast<int>(sound) << endl;
    }
    soundChannel[sound] = -1;
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

    engineSound = Mix_LoadWAV("../data/sound/engine_loop.wav");

    if (engineSound == nullptr)
    {
        cerr << "Failed to load gEngineSound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    return success;
}