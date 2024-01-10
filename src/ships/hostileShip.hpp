
#include "../rendering/collisionObject.hpp"
#include "../physics/physics.hpp"
#include "../physics/collisionModel.hpp"
#include "../prefabs/prefabs.hpp"
#include "ship.hpp"
#include "projectile.hpp"

namespace ships
{
    class HostileShip : public rendering::CollisionObject
    {
        inline static constexpr bool debugObject{false};

        inline static int uniqueId{0};

        inline static constexpr int avoidanceRadius = 250;
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
        bool playerOnLeft{false};
        bool encircleLeft{false};

    public:
        HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 90);
        Projectile *frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player, CollisionModel &collisionModel);
        virtual ~HostileShip()
        {
        }
        void renderObject(SDL_Rect viewport) override;

    private:
        double determineLookAngle(physics::Vector2d playerPos);

        bool avoidCollision(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player);
        void determineTactic(const physics::Vector2d &playerPos);
        void determineRotation(const physics::Vector2d &playerPos);
        void determineSpeed(const physics::Vector2d &playerPos);

        void print(const physics::Vector2d &playerPos);
    };
}