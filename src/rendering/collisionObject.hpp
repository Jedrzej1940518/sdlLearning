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
    // debugging
    inline static bool debugObject{true};
    std::vector<std::unique_ptr<sf::Shape>> debugShapes;
    physics::CollisionParams cpCopy;

  protected:
    const prefabs::Prefab &prefab;
    physics::CollisionParams collisionParams;
    physics::GridPosition gridPosition;
    physics::Circle collisionCircle;

    bool alive{true};
    int hp;

  public:
    CollisionObject(const prefabs::Prefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);
    void collisionCheck(const CollisionObject &oth);
    virtual void handleCollision(const CollisionObject &oth);

    void frameUpdate() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    const std::vector<std::unique_ptr<sf::Shape>> &getDebugShapes() const { return debugShapes; };

    // void renderObject(SDL_Rect viewport) override;
    // void debugRender(SDL_Rect viewport);

    // void printCollisionObject() const;
    void printGridPosition() const;
    // void printSpeed() const;

    // void hit(int dmg);

    // sf::Vector2f getPosition();
    // sf::Vector2f getObjectCenter() const;
    // int getWidth() const;
    // int getHeight() const;
    // int getRadius() const;
    void setGridPosition(physics::GridPosition gP);
    const physics::GridPosition &getGridPosition() const;
    // const Body &getBody() const;
    const physics::Circle &getCollisionCircle() const;
    const sf::Vector2f &getCenter() const;

    // double getMass() const;
    // double getRotation();
    // bool isAlive() const;
    virtual ~CollisionObject()
    {
    }
  };
} // namespace rendering