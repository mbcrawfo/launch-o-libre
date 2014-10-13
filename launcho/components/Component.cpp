#include "Component.h"
#include <cassert>

Component::Component(StrongEntityPtr _parent)
: parent(_parent)
{
  assert(parent.get() != nullptr);
}
