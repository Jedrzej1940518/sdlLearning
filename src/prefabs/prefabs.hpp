#pragma once

#include "utils.hpp"

#include <string>

namespace prefabs
{
	struct Prefab
	{
		sf::Texture *texture;
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
	inline static constexpr int lasherShellDamage = 20;
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

	struct Textures
	{
		sf::Texture background;

		sf::Texture asteroid2;
		sf::Texture asteroid3;
		sf::Texture asteroidBig2;

		sf::Texture lasherShell;
		sf::Texture hammerheadShell;
		sf::Texture scarabShell;
		sf::Texture torpedo;

		sf::Texture lasher;
		sf::Texture hammerhead;
		sf::Texture scarab;
		sf::Texture wolf;
	};

	extern Textures *textures;

	void initTextures();
	void initPrefabs();

	inline Prefab background{nullptr, "background3"};

	inline CollidablePrefab asteroid2{nullptr, "asteroid2", 4, 600, 4, 0.f, 60};
	inline CollidablePrefab asteroid3{nullptr, "asteroid3", 3, 1200, 3, 0.f, 120};
	inline CollidablePrefab asteroidBig2{nullptr, "asteroid1", 2.5, 2000, 2.5f, 0.f, 200};

	// lifetime dmg reload maxVelocity scatterAngle
	inline ProjectilePrefab lasherShell{nullptr, "lasher_shell", lasherShellLifetime, lasherShellDamage, lasherShellReload, lasherShellMaxVelocity, 0};
	inline ProjectilePrefab hammerheadShell{nullptr, "hammerhead_shell", hammerheadShellLifetime, hammerheadShellDamage, hammerheadShellReload, hammerheadShellMaxVelocity, 1.f};
	inline ProjectilePrefab scarabShell{nullptr, "scarab_shell", scarabShellLifetime, scarabShellDamage, scarabShellReload, scarabShellMaxVelocity, 0.f};
	inline ProjectilePrefab torpedo{nullptr, "torpedo", wolfShellLifetime, wolfShellDamage, wolfShellReload, wolfShellMaxVelocity, 0};
	// max_velocity, mass, max_rotation_speed (degrees), max_acceleration, hp, shell
	inline ShipPrefab lasher{nullptr, "lasher", lasherMaxVelocity, lasherMass, lasherMaxRotationSpeed, lasherMaxAcceleration, lasherHp, lasherShell};
	inline ShipPrefab hammerhead{nullptr, "hammerhead", hammerheadMaxVelocity, hammerheadMass, hammerheadMaxRotationSpeed, hammerheadMaxAcceleration, hammerheadHp, hammerheadShell};
	inline ShipPrefab scarab{nullptr, "scarab", scarabMaxVelocity, scarabMass, scarabMaxRotationSpeed, scarabMaxAcceleration, scarabHp, scarabShell};
	inline ShipPrefab wolf{nullptr, "wolf", wolfMaxVelocity, wolfMass, wolfMaxRotationSpeed, wolfMaxAcceleration, wolfHp, torpedo};

}