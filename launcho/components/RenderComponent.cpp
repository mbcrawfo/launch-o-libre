#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "utility/conversions.h"
#include <cassert>

RenderComponent::RenderComponent(StrongEntityPtr _parent, RenderLayer _layer)
:Component(_parent), layer(_layer)
{
}

ComponentID RenderComponent::getID() const
{
  return ID;
}

RenderLayer RenderComponent::getLayer() const
{
  return layer;
}

void RenderComponent::setLayer(RenderLayer newLayer)
{
  layer = newLayer;
}
