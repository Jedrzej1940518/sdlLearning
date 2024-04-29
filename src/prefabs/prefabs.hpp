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

	const inline Prefab background{getDataPath("graphics/backgrounds/background3.jpg"), "background3"};

	const inline CollidablePrefab asteroid2{getDataPath("graphics/asteroids/asteroid2.png"), "asteroid2", 4, 600, 4, 0.f, 60};
	const inline CollidablePrefab asteroid3{getDataPath("graphics/asteroids/asteroid3.png"), "asteroid3", 3, 1200, 3, 0.f, 120};
	const inline CollidablePrefab asteroidBig2{getDataPath("graphics/asteroids/asteroid_big02.png"), "asteroid1", 2.5, 2000, 2.5f, 0.f, 200};

	// lifetime dmg reload maxVelocity scatterAngle
	const inline ProjectilePrefab lasherShell{getDataPath("graphics/projectiles/shell_small_green.png"), "lasher_shell", 40, 2, 40, 7, 5.f};
	const inline ProjectilePrefab hammerheadShell{getDataPath("graphics/projectiles/bomblet2.png"), "hammerhead_shell", 55, 5, 30, 8.5f, 3.f};
	const inline ProjectilePrefab scarabShell{getDataPath("graphics/projectiles/rift_torpedo.png"), "scarab_shell", 40, 5, 30, 10, 3.f};
	const inline ProjectilePrefab torpedo{getDataPath("graphics/projectiles/missile_torpedo_compact.png"), "torpedo", 60, 50, 180, 7, 0};
	// max_velocity, mass, max_rotation_speed (degrees), max_acceleration, hp
	const inline ShipPrefab hammerhead{getDataPath("graphics/ships/hammerhead_dd.png"), "hammerhead", 3.8f, 2500, 3.8f, 0.38f, 300, hammerheadShell};
	const inline ShipPrefab lasher{getDataPath("graphics/ships/lasher_ff.png"), "lasher", 4.5f, 1200, 4.5f, 0.45f, 60, lasherShell};
	const inline ShipPrefab wolf{getDataPath("graphics/ships/wolf_ff.png"), "wolf", 5.5f, 600, 6, 0.7f, 40, torpedo};
	const inline ShipPrefab scarab{getDataPath("graphics/ships/scarab.png"), "scarab", 5, 1000, 5, 0.5f, 1000, scarabShell};

}