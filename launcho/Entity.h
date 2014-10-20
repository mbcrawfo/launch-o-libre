#pragma once

#include "types.h"
#include <map>
#include <memory>

/**
 * Encapsulates an entity in the game world.
 */
class Entity final
{
private:
  // unique id of this entity
  EntityID id;
  // components that make up the entity
	std::map<ComponentTypeID, StrongComponentPtr> components;

public:
  // valid entities have id >= 1
  static const EntityID INVALID_ID = 0;

  // prevent copying
  Entity() = delete;
  Entity(const Entity&) = delete;
  Entity& operator=(Entity) = delete;

  /**
   * Creates a new, empty entity.
   */
  explicit Entity(EntityID myID);

  /**
   * Initializes the entity's components.  Add all components before calling.
   */
	bool initialize();

  /**
   * Update all of the entity's components.
   * @param deltaMs Elapsed time since the last update.
   */
	void update(const float deltaMS);

  /**
   * Destroy the entity and its components.
   */
	void destroy();

  EntityID getID() const;

  /**
   * Add a component to the entity.  May only have one component of each type.
   */
	void addComponent(StrongComponentPtr component);

  /**
   * Retrieves a component from the entity.
   */
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
