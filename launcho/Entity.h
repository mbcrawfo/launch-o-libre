#pragma once

#include "types.h"
#include <map>
#include <memory>

// valid entities have id >= 1
EntityID INVALID_ENTITY_ID = 0;

class Entity
{
private:
  EntityID id;
	std::map<ComponentTypeID, StrongComponentPtr> components;

public:
  Entity(EntityID myID);

	bool initialize();
	void update(const float deltaMS);
	void destroy();

	void addComponent(StrongComponentPtr component);

	template<typename ComponentType>
	std::weak_ptr<ComponentType> getComponent() const;
};

template<typename ComponentType>
std::weak_ptr<ComponentType> Entity::getComponent() const
{
  auto itr = components.find(ComponentType::ID);
  if (itr != components.end())
  {
    auto ptr = static_pointer_cast<ComponentType>(itr->second);
    return std::weak_ptr<ComponentType>(ptr);
  }
  else
  {
    return std::weak_ptr<ComponentType>();
  }
}
