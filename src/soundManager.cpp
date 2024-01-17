#include "soundManager.hpp"
#include "utils.hpp"

#include <SFML/Audio.hpp>

SoundManager::SoundManager()
{
    loadData();
    initUniqueSounds();
}
SoundManager::~SoundManager()
{
}

SoundManager &SoundManager::GetInstance()
{
    static SoundManager soundManager;
    return soundManager;
}

void SoundManager::cleanupDeadSounds()
{
    for (auto it = sounds.begin(); it != sounds.end();)
    {
        if (it->getStatus() == sf::Sound::Stopped)
            it = sounds.erase(it);
        else
            ++it;
    }
}

void SoundManager::clearSounds()
{
    sounds.clear();
}

void SoundManager::switchSound()
{
    static std::vector<Sound> uniqueSoundsSwitched;
    soundOn = !soundOn;

    for (auto &sfSound : sounds)
        soundOn ? sfSound.play() : sfSound.pause();

    if (!soundOn)
    {
        for (auto &[sound, sfSound] : uniqueSounds)
        {
            if (sfSound.getStatus() == sf::Sound::Playing)
            {
                uniqueSoundsSwitched.push_back(sound);
                pauseUniqueSound(sound);
            }
        }
    }
    else
    {
        for (auto sound : uniqueSoundsSwitched)
        {
            playUniqueSound(sound);
        }

        uniqueSoundsSwitched.clear();
    }
}

void SoundManager::playSound(Sound sound)
{
    sf::SoundBuffer &buffer = soundBuffers[sound];
    sounds.push_back(sf::Sound{buffer});
    sounds.back().play();
}

void SoundManager::playUniqueSound(Sound sound)
{
    if (uniqueSounds[sound].getStatus() != sf::Sound::Playing)
        uniqueSounds[sound].play();
}
void SoundManager::pauseUniqueSound(Sound sound)
{
    uniqueSounds[sound].pause();
}

void SoundManager::loadData()
{
    engineSound = getDataPath("data/sound/engine_03_hitek_01_frigate.ogg");
    playerWeaponSound = getDataPath("data/sound/hephaestus_fire_01.ogg");
    shellHitSmallSound = getDataPath("data/sound/gun_hit_light_01.ogg");
    shellHitBigSound = getDataPath("data/sound/gun_hit_heavy_03.ogg");
    collisionSound = getDataPath("data/sound/collision_asteroid_vs_asteroid_01.ogg");

    soundPaths[Sound::PLAYER_WEAPON] = playerWeaponSound;
    soundPaths[Sound::ENGINE] = engineSound;
    soundPaths[Sound::SHELL_HIT_SMALL] = shellHitSmallSound;
    soundPaths[Sound::SHELL_HIT_BIG] = shellHitBigSound;
    soundPaths[Sound::COLLISION] = collisionSound;

    for (const auto &[sound, path] : soundPaths)
    {
        sf::SoundBuffer buffer;

        if (!buffer.loadFromFile(soundPaths[sound]))
            std::cerr << "Error loading sound from a file! path: " << soundPaths[sound] << std::endl;

        soundBuffers[sound] = buffer;
    }
}

void SoundManager::initUniqueSounds()
{
    for (Sound sound : uniqueSoundSet)
    {
        sf::SoundBuffer &buffer = soundBuffers[sound];
        uniqueSounds[sound] = {sf::Sound{buffer}};
        uniqueSounds[sound].setLoop(true);
    }
}