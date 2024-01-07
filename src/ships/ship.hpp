
#include "../rendering/collisionObject.hpp"
#include "../physics/physics.hpp"
#include "../physics/collisionModel.hpp"
#include "../prefabs/prefabs.hpp"

namespace ships
{
    struct Projectile : public rendering::CollisionObject
    {
        Projectile(prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0) : CollisionObject(projectilePrefab, position, speed, rotation), lifetime{projectilePrefab.lifetime} {}
        int lifetime;
        bool alive{true};

        void frameUpdate(physics::CollisionModel &collisionModel)
        {
            CollisionObject::frameUpdate(collisionModel);
            --lifetime;
            alive = lifetime > 0;
        };
        bool isAlive() const { return alive; }
        virtual ~Projectile()
        {
        }
    };

    class Ship : public rendering::CollisionObject
    {
        bool inputDirections[4];
        bool spawnProjectile;

    public:
        Ship(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);

        void shoot();

        void addInput(physics::DIRECTION dir);
        void removeInput(physics::DIRECTION dir);

        void rotateLeft();
        void rotateRight();
        void stopRotateLeft();
        void stopRotateRight();

        Projectile *frameUpdate();
    };
}