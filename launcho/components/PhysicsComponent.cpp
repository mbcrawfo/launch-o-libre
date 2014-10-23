#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "utility/Log.h"

static const Vector2 GRAVITY(0.0f, -9.80665f);

PhysicsComponent::PhysicsComponent(StrongEntityPtr parent, 
                                   const Vector2& initialVel)
: Component(parent),
  velocity(initialVel),
  acceleration(Vector2::ZERO),
  gravityEnabled(true),
  physicsEnabled(true)
{
}

ComponentID PhysicsComponent::getID() const
{
  return ID;
}

void PhysicsComponent::update(const float deltaMs)
{
  if (isStatic() || deltaMs <= 0.0f)
  {
    return;
  }

  float deltaS = deltaMs / 1000.0f;
  Vector2 deltaV = acceleration * deltaS;
  if (gravityEnabled)
  {
    deltaV += GRAVITY * deltaS;
  }
  velocity += deltaV;

  auto tc = parent->getComponent<TransformComponent>().lock();
  Vector2 displacement = velocity * deltaS;
  tc->move(displacement);
}

const Vector2& PhysicsComponent::getVelocity() const
{
  return velocity;
}

void PhysicsComponent::setVelocity(const Vector2& vel)
{
  if (physicsEnabled)
  {
    velocity = vel;
  }
}

void PhysicsComponent::modVelocity(const Vector2& offset)
{
  setVelocity(velocity + offset);
}

const Vector2& PhysicsComponent::getAcceleration() const
{
  return acceleration;
}

void PhysicsComponent::setAcceleration(const Vector2& acc)
{
  if (physicsEnabled)
  {
    acceleration = acc;
  }  
}

void PhysicsComponent::modAcceleration(const Vector2& offset)
{
  setAcceleration(acceleration + offset);
}

bool PhysicsComponent::hasGravity() const
{
  return gravityEnabled;
}

void PhysicsComponent::enableGravity(bool state)
{
  gravityEnabled = state;
}

bool PhysicsComponent::isStatic() const
{
  return !physicsEnabled;
}

void PhysicsComponent::enablePhysics(bool state)
{
  physicsEnabled = state;
  if (!physicsEnabled)
  {
    velocity = Vector2::ZERO;
    acceleration = Vector2::ZERO;
  }
}
