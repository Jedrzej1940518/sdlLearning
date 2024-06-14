#include "prefabs.hpp"

namespace prefabs
{
    Textures *textures{nullptr};

    void initTextures()
    {
        textures = new Textures();
        textures->background.loadFromFile(getDataPath("graphics/backgrounds/background3.jpg"));

        textures->asteroid2.loadFromFile(getDataPath("graphics/asteroids/asteroid2.png"));
        textures->asteroid3.loadFromFile(getDataPath("graphics/asteroids/asteroid3.png"));
        textures->asteroidBig2.loadFromFile(getDataPath("graphics/asteroids/asteroid_big02.png"));

        textures->lasherShell.loadFromFile(getDataPath("graphics/projectiles/shell_small_green.png"));
        textures->hammerheadShell.loadFromFile(getDataPath("graphics/projectiles/bomblet2.png"));
        textures->scarabShell.loadFromFile(getDataPath("graphics/projectiles/rift_torpedo.png"));
        textures->torpedo.loadFromFile(getDataPath("graphics/projectiles/missile_torpedo_compact.png"));

        textures->lasher.loadFromFile(getDataPath("graphics/ships/lasher_ff.png"));
        textures->hammerhead.loadFromFile(getDataPath("graphics/ships/hammerhead_dd.png"));
        textures->scarab.loadFromFile(getDataPath("graphics/ships/scarab.png"));
        textures->wolf.loadFromFile(getDataPath("graphics/ships/wolf_ff.png"));

        textures->lasher.setSmooth(true);
        textures->hammerhead.setSmooth(true);
        textures->scarab.setSmooth(true);
        textures->wolf.setSmooth(true);
    }

    void initPrefabs()
    {
        background.texture = &(textures->background);

        asteroid2.texture = &(textures->asteroid2);
        asteroid3.texture = &(textures->asteroid3);
        asteroidBig2.texture = &(textures->asteroidBig2);

        lasherShell.texture = &(textures->lasherShell);
        hammerheadShell.texture = &(textures->hammerheadShell);
        scarabShell.texture = &(textures->scarabShell);
        torpedo.texture = &(textures->torpedo);

        lasher.texture = &(textures->lasher);
        hammerhead.texture = &(textures->hammerhead);
        scarab.texture = &(textures->scarab);
        wolf.texture = &(textures->wolf);
    }

}