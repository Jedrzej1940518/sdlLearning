#pragma once

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
#include <SFML/Audio.hpp>

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
    inline static std::set<Sound> uniqueSoundSet{Sound::ENGINE};

    inline static std::string music = "";
    inline static std::string engineSound = "";
    inline static std::string playerWeaponSound = "";
    inline static std::string shellHitSmallSound = "";
    inline static std::string shellHitBigSound = "";
    inline static std::string collisionSound = "";

    inline static std::unordered_map<Sound, std::string> soundPaths;
    inline static std::unordered_map<Sound, sf::SoundBuffer> soundBuffers;

    inline static std::list<sf::Sound> sounds;
    inline static std::unordered_map<Sound, sf::Sound> uniqueSounds;

    bool soundOn{false};

    SoundManager();
    ~SoundManager();

    void initUniqueSounds();
    void loadData();

public:
    static SoundManager &GetInstance();

    void playSound(Sound sound);
    void cleanupDeadSounds();

    void switchSound();
    void clearSounds();

    void playUniqueSound(Sound sound);
    void pauseUniqueSound(Sound sound);

    SoundManager(SoundManager &other) = delete;
    void operator=(const SoundManager &) = delete;
};