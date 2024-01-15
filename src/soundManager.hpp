#pragma once

#include <map>


enum class Sound
{
    ENGINE = 1,
    PLAYER_WEAPON,
    SHELL_HIT_SMALL,
    SHELL_HIT_BIG,
    COLLISION
};

// singleton

class SoundManager
{
private:
    constexpr static int audioFrequency = 44100;
    constexpr static int hardwareChannels = 2;
    constexpr static int audioChunkSize = 2048;

    // inline static Mix_Music *music = nullptr;

    // inline static Mix_Chunk *engineSound = nullptr;
    // inline static Mix_Chunk *playerWeaponSound = nullptr;
    // inline static Mix_Chunk *shellHitSmallSound = nullptr;
    // inline static Mix_Chunk *shellHitBigSound = nullptr;
    // inline static Mix_Chunk *collisionSound = nullptr;

    bool sound{false};

    SoundManager();
    ~SoundManager();

    // inline static std::map<Sound, Mix_Chunk *> chunkPtr;
    static constexpr int fadeMs = 300;
    bool loadData();
    bool initAudio();

public:
    static SoundManager &GetInstance();

    void playMusic();
    void pauseMusic();

    void playSound(Sound sound);
    void switchSound();

    SoundManager(SoundManager &other) = delete;
    void operator=(const SoundManager &) = delete;
};