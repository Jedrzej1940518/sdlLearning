
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
        int rotationTicks{5};
        bool playerOnLeft{false};

    public:
        HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);
        Projectile *frameUpdate(const vector<HostileShip *> & /*allies*/, Ship &player);

    private:
        double determineLookAngle(physics::Vector2d playerPos);
    };
}