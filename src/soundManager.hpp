#pragma once

#include <map>
#include <SDL2/SDL_mixer.h>

enum class Sound
{
    ENGINE = 1,
};

// singleton

class SoundManager
{
private:
    constexpr static int audioFrequency = 44100;
    constexpr static int hardwareChannels = 2;
    constexpr static int audioChunkSize = 2048;

    inline static Mix_Music *music = nullptr;
    inline static Mix_Chunk *engineSound = nullptr;

    SoundManager();
    ~SoundManager();
    inline static std::map<Sound, int> soundChannel;
    static constexpr int fadeMs = 300;
    bool loadData();
    bool initAudio();

public:
    static SoundManager &GetInstance();

    void playMusic();
    void pauseMusic();

    void playSound(Sound sound);
    void pauseSound(Sound sound);

    SoundManager(SoundManager &other) = delete;
    void operator=(const SoundManager &) = delete;
};