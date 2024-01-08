
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
        enum Tactic
        {
            approach,
            disapproach
        };
        Tactic tactic{approach};

        int rotationTicks{5};
        int tacticTicks{5};
        bool playerOnLeft{false};

    public:
        HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);
        Projectile *frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player, CollisionModel &collisionModel);
        virtual ~HostileShip()
        {
        }

    private:
        double determineLookAngle(physics::Vector2d playerPos);
        void determineRotation(const physics::Vector2d &playerPos);
        void determineSpeed(const physics::Vector2d &playerPos);
    };
}