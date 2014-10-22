#pragma once

#include "Component.h"
#include "types.h"
#include "math/AABB2.h"

class TransformComponent;
using StrongTransformComponentPtr = std::shared_ptr<TransformComponent>;
using WeakTransformComponentPtr = std::weak_ptr<TransformComponent>;

class TransformComponent
  : public Component
{
private:
  // clockwise rotation around the Z axis (projected out of screen)
  // with 0 degrees being oriented to the right (positive x axis)
  // maintains a value in the range [0, 360)
  float rotation;
  // position and size of object
  AABB2 bounds;

public:
  static const ComponentID ID = 0x2e15c002;  

  explicit TransformComponent(StrongEntityPtr _parent);
  ComponentID getID() const override;

  float getRotation() const;
  void setRotation(float degrees);
  void rotate(float degrees);

  const AABB2& getBounds() const;

  // the position is the center of the object
  const Vector2& getPosition() const;
  void setPosition(const Vector2& pos);
  void move(const Vector2& offset);

  float getWidth() const;
  float getHeight() const;  
  void setWidth(float width);
  void setHeight(float height);
  void setSize(float width, float height);

  Vector2 getLowerLeftCorner() const;
  Vector2 getUpperLeftCorner() const;
  Vector2 getUpperRightCorner() const;
  Vector2 getLowerRightCorner() const;
};