#pragma once

#include "utils.hpp"
#include "object.hpp"
#include "physics/body.hpp"
#include "physics/physics.hpp"
#include "prefabs/prefabs.hpp"

#include <memory>

#include <SFML/Graphics/Shape.hpp>

namespace rendering
{
  class CollisionObject : public Object
  {
    inline static bool debugObject{true};

  protected:
    std::vector<std::unique_ptr<sf::Shape>> shapesToDraw;

    physics::CollisionParams collisionParams;
    physics::GridPosition gridPosition;

    bool alive{true};
    const int maxHp;
    int hp;

    void addDebugObjects();
    void addHpBar();

  public:
    CollisionObject(const prefabs::CollidablePrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);

    bool collisionHappening(const physics::Circle &colliisonCircle);
    void handleCollision(const CollisionObject &oth);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void frameUpdate() override;
    void hit(int dmg);

    // setters
    void setGridPosition(physics::GridPosition gp) { gridPosition = gp; };

    // getters
    const physics::Circle getCollisionCircle() const { return physics::Circle{getCenter(), spriteRadius}; };
    const physics::GridPosition &getGridPosition() const { return gridPosition; }
    const sf::Vector2f &getCenter() const { return body.getPosition(); };

    float getMass() const { return body.getMass(); };
    bool isAlive() const { return alive; };

    virtual ~CollisionObject() {}
  };
} // namespace rendering