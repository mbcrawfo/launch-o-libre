#pragma once

#include "Component.h"
#include "Box2D.h"

class PhysicsComponent;
using StrongPhysicsComponentPtr = std::shared_ptr<PhysicsComponent>;
using WeakPhysicsComponentPtr = std::weak_ptr<PhysicsComponent>;

class PhysicsComponent
  : public Component
{
public:
  enum class Type
  {
    Static,
    Dynamic
  };

private:    
  b2Body* body;
  Type type;

public:
  static const ComponentID ID = 0xF2A12A9B;

  PhysicsComponent(StrongEntityPtr parent, Type type);

  ComponentID getID() const override;
  bool initialize() override;
  void update(const float deltaMs) override;
  void destroy() override;
};