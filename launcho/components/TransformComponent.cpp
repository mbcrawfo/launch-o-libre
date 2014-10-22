#include "TransformComponent.h"
#include <cassert>

TransformComponent::TransformComponent(StrongEntityPtr _parent)
: Component(_parent), rotation(0.0f), bounds()
{
}

ComponentID TransformComponent::getID() const
{
  return ID;
}

float TransformComponent::getRotation() const
{
  return rotation;
}

void TransformComponent::setRotation(float degrees)
{
  rotation = degrees;
  if (rotation >= 360.0f)
  {
    rotation -= 360.0f;
  }
  else if (rotation < 0.0f)
  {
    rotation += 360.0f;
  }
}

void TransformComponent::rotate(float degrees)
{
  setRotation(rotation + degrees);
}

const AABB2& TransformComponent::getBounds() const
{
  return bounds;
}

const Vector2& TransformComponent::getPosition() const
{
  return bounds.center;
}

void TransformComponent::setPosition(const Vector2& pos)
{
  bounds.center = pos;
}

void TransformComponent::move(const Vector2& offset)
{
  bounds.center += offset;
}

float TransformComponent::getWidth() const
{
  return bounds.width();
}

float TransformComponent::getHeight() const
{
  return bounds.height();
}

void TransformComponent::setWidth(float width)
{
  assert(width > 0.0f);
  bounds.halfSize.x = width / 2.0f;
}

void TransformComponent::setHeight(float height)
{
  assert(height > 0.0f);
  bounds.halfSize.y = height / 2.0f;
}

void TransformComponent::setSize(float width, float height)
{
  setWidth(width);
  setHeight(height);
}

Vector2 TransformComponent::getLowerLeftCorner() const
{
  return bounds.center - bounds.halfSize;
}

Vector2 TransformComponent::getUpperLeftCorner() const
{
  return bounds.center + Vector2(-bounds.halfSize.x, bounds.halfSize.y);
}

Vector2 TransformComponent::getUpperRightCorner() const
{
  return bounds.center + bounds.halfSize;
}

Vector2 TransformComponent::getLowerRightCorner() const
{
  return bounds.center + Vector2(bounds.halfSize.x, -bounds.halfSize.y);
}

