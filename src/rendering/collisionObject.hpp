#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "object.hpp"
#include "../prefabs/prefabs.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{
  class CollisionModel;
};

namespace rendering
{
  class CollisionObject : public Object
  {
  protected:
    using Body = physics::Body;
    using CollisionModel = physics::CollisionModel;
    using Vector2d = physics::Vector2d;

    const prefabs::Prefab &prefab;
    Body body;
    physics::CollisionParams collisionParams;
    physics::GridPosition gridPosition;
    bool alive{true};
    int hp;

  public:
    CollisionObject(const prefabs::Prefab &prefab, Vector2d position, Vector2d speed = {0, 0}, double rotation = 0);
    void collisionCheck(CollisionObject &oth);
    virtual void handleCollision(CollisionObject &oth);

    void frameUpdate(physics::CollisionModel &collisionModel);
    void renderObject(SDL_Rect viewport) override;
    void printCollisionObject() const;
    void printGridPosition() const;
    void printSpeed() const;

    void hit(int dmg);

    physics::Vector2d getPosition();
    physics::Vector2d getObjectCenter();
    int getWidth() const;
    int getHeight() const;
    physics::GridPosition &getGridPosition();
    const physics::GridPosition &getGridPosition() const;
    Body &getBody();
    double getRotation();
    bool isAlive() const;
    virtual ~CollisionObject()
    {
    }
  };
} // namespace rendering