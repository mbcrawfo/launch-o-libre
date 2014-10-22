#include "Entity.h"
#include "components/Component.h"
#include <stdexcept>
#include <cassert>

Entity::Entity(EntityID myID, const std::string& name)
: id(myID), components(), name(name)
{
  assert(id != Entity::INVALID_ID);
}

const char* Entity::getNameC() const
{
  return name.c_str();
}

const std::string& Entity::getName() const
{
  return name;
}

bool Entity::initialize()
{
  for (auto component : components)
  {
    if (!component.second->initialize())
    {
      return false;
    }
  }

  return true;
}

void Entity::update(const float deltaMS)
{
  for (auto component : components)
  {
    component.second->update(deltaMS);
  }
}

void Entity::destroy()
{
  for (auto component : components)
  {
    component.second->destroy();
  }
}

EntityID Entity::getID() const
{
  return id;
}

void Entity::addComponent(StrongComponentPtr component)
{
  assert(component.get() != nullptr);
  assert(components.find(component->getID()) == components.end());
  components[component->getID()] = component;
}

