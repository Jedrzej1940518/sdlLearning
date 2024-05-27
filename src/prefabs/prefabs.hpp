#pragma once

#include "utils.hpp"

#include <string>

namespace prefabs
{
	struct Prefab
	{
		const std::string texturePath;
		const std::string id;
	};

	struct ProjectilePrefab : Prefab
	{
		int lifetime;
		int dmg;
		int reload;
		float maxVelocity;
		float scatterAngle;
	};

	struct ObjectPrefab : Prefab
	{
		float maxVelocity;
		float mass;
		float maxRotationSpeed;
		float maxAcceleration;
	};

	struct CollidablePrefab : ObjectPrefab
	{
		int hp;
	};

	struct ShipPrefab : CollidablePrefab
	{
		const ProjectilePrefab &weaponPrefab;
	};

	// lasher shell
	inline static constexpr int lasherShellLifetime = (int)(20 / config::PREFAB_MULTIPLIER);
	inline static constexpr int lasherShellDamage = 10;
	inline static constexpr int lasherShellReload = (int)(15 / config::PREFAB_MULTIPLIER);
	inline static constexpr float lasherShellMaxVelocity = 20.f * config::PREFAB_MULTIPLIER;
	// lasher
	inline static constexpr float lasherMaxVelocity = 4.6f * config::PREFAB_MULTIPLIER;
	inline static constexpr int lasherMass = 9999;
	inline static constexpr float lasherMaxRotationSpeed = 10.f * config::PREFAB_MULTIPLIER;
	inline static constexpr float lasherMaxAcceleration = 0.6f * config::PREFAB_MULTIPLIER;
	inline static constexpr int lasherHp = 150;
	// hammerhead shell
	inline static constexpr int hammerheadShellLifetime = (int)(30 / config::PREFAB_MULTIPLIER);
	inline static constexpr int hammerheadShellDamage = 3;
	inline static constexpr int hammerheadShellReload = (int)(30 / config::PREFAB_MULTIPLIER);
	inline static constexpr float hammerheadShellMaxVelocity = 22.f * config::PREFAB_MULTIPLIER;
	// hammerhead
	inline static constexpr float hammerheadMaxVelocity = 3.2f * config::PREFAB_MULTIPLIER;
	inline static constexpr int hammerheadMass = 2500;
	inline static constexpr float hammerheadMaxRotationSpeed = 2.f * config::PREFAB_MULTIPLIER;
	inline static constexpr float hammerheadMaxAcceleration = 0.2f * config::PREFAB_MULTIPLIER;
	inline static constexpr int hammerheadHp = 200;
	// scarab shell
	inline static constexpr int scarabShellLifetime = (int)(25 / config::PREFAB_MULTIPLIER);
	inline static constexpr int scarabShellDamage = 1;
	inline static constexpr int scarabShellReload = (int)(15 / config::PREFAB_MULTIPLIER);
	inline static constexpr float scarabShellMaxVelocity = 20.f * config::PREFAB_MULTIPLIER;
	// scarab
	inline static constexpr float scarabMaxVelocity = 4.3f * config::PREFAB_MULTIPLIER;
	inline static constexpr int scarabMass = 1000;
	inline static constexpr float scarabMaxRotationSpeed = 3.f * config::PREFAB_MULTIPLIER;
	inline static constexpr float scarabMaxAcceleration = 0.5f * config::PREFAB_MULTIPLIER;
	inline static constexpr int scarabHp = 100;
	// wolf shell
	inline static constexpr int wolfShellLifetime = (int)(30 / config::PREFAB_MULTIPLIER);
	inline static constexpr int wolfShellDamage = 10;
	inline static constexpr int wolfShellReload = (int)(90 / config::PREFAB_MULTIPLIER);
	inline static constexpr float wolfShellMaxVelocity = 25.f * config::PREFAB_MULTIPLIER;
	// wolf
	inline static constexpr float wolfMaxVelocity = 5.5f * config::PREFAB_MULTIPLIER;
	inline static constexpr int wolfMass = 600;
	inline static constexpr float wolfMaxRotationSpeed = 10.f * config::PREFAB_MULTIPLIER;
	inline static constexpr float wolfMaxAcceleration = 0.7f * config::PREFAB_MULTIPLIER;
	inline static constexpr int wolfHp = 40;

	const inline Prefab background{getDataPath("graphics/backgrounds/background3.jpg"), "background3"};

	const inline CollidablePrefab asteroid2{getDataPath("graphics/asteroids/asteroid2.png"), "asteroid2", 4, 600, 4, 0.f, 60};
	const inline CollidablePrefab asteroid3{getDataPath("graphics/asteroids/asteroid3.png"), "asteroid3", 3, 1200, 3, 0.f, 120};
	const inline CollidablePrefab asteroidBig2{getDataPath("graphics/asteroids/asteroid_big02.png"), "asteroid1", 2.5, 2000, 2.5f, 0.f, 200};

	// lifetime dmg reload maxVelocity scatterAngle
	const inline ProjectilePrefab lasherShell{getDataPath("graphics/projectiles/shell_small_green.png"), "lasher_shell", lasherShellLifetime, lasherShellDamage, lasherShellReload, lasherShellMaxVelocity, 0};
	const inline ProjectilePrefab hammerheadShell{getDataPath("graphics/projectiles/bomblet2.png"), "hammerhead_shell", hammerheadShellLifetime, hammerheadShellDamage, hammerheadShellReload, hammerheadShellMaxVelocity, 1.f};
	const inline ProjectilePrefab scarabShell{getDataPath("graphics/projectiles/rift_torpedo.png"), "scarab_shell", scarabShellLifetime, scarabShellDamage, scarabShellReload, scarabShellMaxVelocity, 0.f};
	const inline ProjectilePrefab torpedo{getDataPath("graphics/projectiles/missile_torpedo_compact.png"), "torpedo", wolfShellLifetime, wolfShellDamage, wolfShellReload, wolfShellMaxVelocity, 0};
	// max_velocity, mass, max_rotation_speed (degrees), max_acceleration, hp, shell
	const inline ShipPrefab lasher{getDataPath("graphics/ships/lasher_ff.png"), "lasher", lasherMaxVelocity, lasherMass, lasherMaxRotationSpeed, lasherMaxAcceleration, lasherHp, lasherShell};
	const inline ShipPrefab hammerhead{getDataPath("graphics/ships/hammerhead_dd.png"), "hammerhead", hammerheadMaxVelocity, hammerheadMass, hammerheadMaxRotationSpeed, hammerheadMaxAcceleration, hammerheadHp, hammerheadShell};
	const inline ShipPrefab scarab{getDataPath("graphics/ships/scarab.png"), "scarab", scarabMaxVelocity, scarabMass, scarabMaxRotationSpeed, scarabMaxAcceleration, scarabHp, scarabShell};
	const inline ShipPrefab wolf{getDataPath("graphics/ships/wolf_ff.png"), "wolf", wolfMaxVelocity, wolfMass, wolfMaxRotationSpeed, wolfMaxAcceleration, wolfHp, torpedo};

}