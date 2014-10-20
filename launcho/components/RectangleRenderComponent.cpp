#include "RectangleRenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "utility/conversions.h"
#include <cassert>

RectangleRenderComponent::RectangleRenderComponent(StrongEntityPtr _parent)
  :Component(_parent)
{
}

ComponentTypeID RectangleRenderComponent::getID() const
{
  return ID;
}

bool RectangleRenderComponent::initialize()
{
  auto transform = parent->getComponent<TransformComponent>().lock();
  assert(transform.get() != nullptr);

  rect.setPosition(convert(transform->position));

  return true;
}

void RectangleRenderComponent::destroy()
{
  parent = StrongEntityPtr();
}

