#pragma once

#include "Component.h"
#include "types.h"
#include "math/Vector2.h"

class TransformComponent
  : public Component
{
public:
  static const ComponentTypeID ID = 0x2e15c002;

  float rotation; // TODO: determine units and origin for this
  Vector2 position; // meters from origin
  Vector2 velocity; // meters / sec

  TransformComponent(StrongEntityPtr _parent);
  ComponentTypeID getID() const override;
  void destroy() override;
};