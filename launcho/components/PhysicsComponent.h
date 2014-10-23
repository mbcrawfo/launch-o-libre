#pragma once

#include "Component.h"
#include "math/Vector2.h"

class PhysicsComponent;
using StrongPhysicsComponentPtr = std::shared_ptr<PhysicsComponent>;
using WeakPhysicsComponentPtr = std::weak_ptr<PhysicsComponent>;

class PhysicsComponent
  : public Component
{
private:    
  Vector2 velocity;
  Vector2 acceleration;
  bool gravityEnabled;
  bool physicsEnabled;

public:
  static const ComponentID ID = 0xF2A12A9B;

  PhysicsComponent(StrongEntityPtr parent, 
                   const Vector2& initialVel = Vector2::ZERO);

  ComponentID getID() const override;
  void update(const float deltaMs) override;

  const Vector2& getVelocity() const;
  void setVelocity(const Vector2& vel);
  void modVelocity(const Vector2& offset);

  // at this point acceleration is constant, does not change until you 
  // modify it
  const Vector2& getAcceleration() const;
  void setAcceleration(const Vector2& acc);
  void modAcceleration(const Vector2& offset);

  // objects without gravity float around like 0g
  bool hasGravity() const;
  void enableGravity(bool state);

  // static objects do not use physics for movement
  bool isStatic() const;
  void enablePhysics(bool state);
};