#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "utility/Log.h"
#include "Game.h"
#include "Box2DPhysics.h"
#include "utility/conversions.h"

static const Vector2 GRAVITY(0.0f, -9.80665f);

PhysicsComponent::PhysicsComponent(StrongEntityPtr parent, Type type)
: Component(parent),
  body(nullptr),
  type(type)
{
}

ComponentID PhysicsComponent::getID() const
{
  return ID;
}

bool PhysicsComponent::initialize()
{
  auto world = Game::getInstance().getPhysicsSystem()->getWorld().lock();
  auto tc = parent->getComponent<TransformComponent>().lock();

  b2BodyDef bodyDef;  
  bodyDef.type = type == Type::Static ? b2_staticBody : b2_dynamicBody;
  bodyDef.position.Set(tc->getPosition().x, tc->getPosition().y);
  bodyDef.fixedRotation = true;
  bodyDef.userData = reinterpret_cast<void*>(parent->getID());
  body = world->CreateBody(&bodyDef);

  b2PolygonShape shape;
  shape.SetAsBox(tc->getBounds().halfSize.x, tc->getBounds().halfSize.y);
  b2FixtureDef fixture;
  fixture.shape = &shape;
  fixture.density = 0.0001f;
  fixture.friction = 0.25f;
  fixture.restitution = 0.5f;
  body->CreateFixture(&fixture);

  return true;
}

void PhysicsComponent::update(const float deltaMs)
{
}

void PhysicsComponent::destroy()
{
  auto world = Game::getInstance().getPhysicsSystem()->getWorld().lock();
  world->DestroyBody(body);
  body = nullptr;
}

void PhysicsComponent::applyImpulse(const Vector2& impulse)
{
  b2Vec2 temp(impulse.x, impulse.y);
  body->ApplyLinearImpulse(temp, body->GetWorldCenter(), true);
}
