#include "TransformComponent.h"

TransformComponent::TransformComponent(StrongEntityPtr _parent)
  : Component(_parent)
{
}

ComponentTypeID TransformComponent::getID() const
{
  return ID;
}
