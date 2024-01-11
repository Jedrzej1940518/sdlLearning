
#include "rendering/collisionObject.hpp"
#include "physics/physics.hpp"
#include "physics/collisionModel.hpp"
#include "prefabs/prefabs.hpp"
#include "ship.hpp"
#include "projectile.hpp"

namespace ships
{
    class HostileShip : public rendering::CollisionObject
    {
        inline static int uniqueId{0};

        int avoidanceRadius;
        inline static constexpr int maxPlayerDist = 600;

        int shipId;

        enum Tactic
        {
            encircle,
            approach,
            disapproach
        };
        Tactic tactic{approach};

        int rotationTicks{5};
        int tacticTicks{5};
        int reloadTicks{0};
        bool playerOnLeft{false};
        bool encircleLeft{false};
        const prefabs::ProjectilePrefab &projectilePrefab;

    public:
        HostileShip(const prefabs::Prefab &prefab, const prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d velocity = {0, 0}, double rotation = 90);
        Projectile *frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, const Ship &player, CollisionModel &collisionModel);
        virtual ~HostileShip()
        {
        }
        void renderObject(SDL_Rect viewport) override;

    private:
        void determineTactic(const physics::Vector2d &playerPos);

        bool avoidCollision(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, const Ship &player);
        void determineSpeed(const physics::Vector2d &playerPos);

        double determineLookAngle(const Ship &player);
        void determineRotation(const Ship &player);

        Projectile *shoot(const physics::Vector2d &playerPos);

        void debugRender(SDL_Rect viewport);
        void print(const physics::Vector2d &playerPos);
    };
}