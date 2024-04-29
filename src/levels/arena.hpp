#pragma once

#include "utils.hpp"
#include "level.hpp"
#include "observationFactory.hpp"

#include "rendering/object.hpp"
#include "rendering/collisionObject.hpp"
#include "physics/collisionModel.hpp"

#include "ships/playerShip.hpp"
#include "ships/aiShip.hpp"
#include "ships/projectile.hpp"

#include <vector>
#include <type_traits>

#include <SFML/Graphics/Drawable.hpp>
#include <opencv2/opencv.hpp>

namespace levels
{

	class Arena : public Level
	{
	public:
		using ObservationType = ObservationFactory::ObservationType;
		using StepType = std::tuple<ObservationType, int, bool>; // obs, reward, done

	private:
		// size from -x, x
		//  to -y, y
		int x = 5000;
		int y = 5000;

		int redTeam = 0;
		int blueTeam = 1;

		int asteroids_number{0};

		bool paused{false};
		bool recordVideo{false};
		int episodeNumber{0};

		std::shared_ptr<cv::VideoWriter> videoWriter;

		std::vector<std::shared_ptr<sf::Drawable>> drawables;
		std::vector<std::shared_ptr<FrameUpdateable>> frameUpdateables;

		std::vector<std::shared_ptr<rendering::CollisionObject>> collidables;
		std::vector<std::shared_ptr<ships::Projectile>> projectiles;

		std::vector<std::shared_ptr<ships::Ship>> shooters;

		std::vector<std::shared_ptr<ships::AiShip>> aiShips;

		std::vector<std::shared_ptr<ships::Ship>> hostileShips;
		std::vector<std::shared_ptr<ships::Ship>> playerShips;

		std::shared_ptr<ships::PlayerShip> controledObject;

		std::shared_ptr<ships::AiShip> neuralNetworkShip;

		physics::CollisionModel collisionModel{};

		int teamHp{0};
		int enemyHp{0};

	public:
		Arena(LevelType &level);
		virtual ~Arena();
		virtual void handleEvents(const sf::Event &event) override;

		StepType step(ships::Tactic::TacticOutcome tactic, int frameSkip);
		ObservationType reset(bool recordEpisode = false);
		ObservationType make_obs();
		void draw();

	private:
		void recordFrame();
		void populateArenaWithAsteroids(int n);

		void cleanupDeadObjects();
		void frameUpdate();
		virtual void render() override;

		template <typename F>
		void doOnEveryContainer(F &&func)
		{
			func(drawables);
			func(frameUpdateables);
			func(collidables);
			func(projectiles);
			func(aiShips);
			func(shooters);
			func(playerShips);
			func(hostileShips);
		}

		template <typename T, typename F>
		void doOnBaseContainers(F &&func, int team = 0)
		{
			if constexpr (std::is_base_of_v<sf::Drawable, T>)
				func(drawables);
			if constexpr (std::is_base_of_v<FrameUpdateable, T>)
				func(frameUpdateables);
			if constexpr (std::is_base_of_v<rendering::CollisionObject, T>)
				func(collidables);
			if constexpr (std::is_base_of_v<ships::Projectile, T>)
				func(projectiles);
			if constexpr (std::is_base_of_v<ships::AiShip, T>)
				func(aiShips);
			if constexpr (std::is_base_of_v<ships::Ship, T>)
			{
				func(shooters);
				team == redTeam ? func(playerShips) : func(hostileShips);
			}
		}

		// templated
		template <typename T>
		void addObject(std::shared_ptr<T> obj, int team = 0)
		{
			auto pushBack = [&obj]<typename Container>(Container &c)
			{
				c.push_back(obj);
			};

			doOnBaseContainers<T>(pushBack, team);
			if constexpr (std::is_base_of_v<ships::Projectile, T> || std::is_base_of_v<rendering::CollisionObject, T>)
				collisionModel.add(obj);

			if constexpr (std::is_base_of_v<ships::PlayerShip, T>)
				controledObject = obj;
		}

		void cleanupDeads()
		{
			auto isDead = [](const auto &obj)
			{
				auto killable = std::dynamic_pointer_cast<Killable>(obj);
				return killable && (not killable->isAlive());
			};
			auto cleanupVector = [&isDead]<typename Vec>(Vec &vec)
			{
				vec.erase(std::remove_if(vec.begin(), vec.end(), isDead), vec.end());
			};

			doOnEveryContainer(cleanupVector);
		}
		void clear()
		{
			auto clearVec = []<typename Vec>(Vec &vec)
			{
				vec.clear();
			};
			doOnEveryContainer(clearVec);
			collisionModel.clear();
		}
		// debug
		void debugPrint();
	};
} // namespace levels