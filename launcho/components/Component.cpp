#include "Component.h"
#include <cassert>

Component::Component(StrongEntityPtr _parent)
: parent(_parent)
{
  assert(parent != nullptr);
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
