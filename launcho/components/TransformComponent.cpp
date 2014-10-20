#include "TransformComponent.h"

TransformComponent::TransformComponent(StrongEntityPtr _parent)
  : Component(_parent)
{
}

ComponentID TransformComponent::getID() const
{
  return ID;
}
