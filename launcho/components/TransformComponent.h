#pragma once

#include "Component.h"
#include "types.h"
#include "math/Vector2.h"

class TransformComponent
  : public Component
{
public:
  static const ComponentID ID = 0x2e15c002;

  float rotation; // TODO: determine units and origin for this
  Vector2 position; // meters from origin

  explicit TransformComponent(StrongEntityPtr _parent);
  ComponentID getID() const override;
};