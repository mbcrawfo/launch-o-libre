#include "Component.h"
#include "Entity.h"
#include <cassert>

Component::Component(StrongEntityPtr _parent)
: parent(_parent)
{
  assert(parent != nullptr);
}

EntityID Component::getParentID() const
{
  return parent->getID();
}

bool Component::initialize()
{
  return true;
}

void Component::update(const float deltaMs)
{
}

void Component::destroy()
{
  parent = StrongEntityPtr();
}
