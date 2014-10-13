#pragma once

#include <cstdint>
#include <memory>

// Used to identify entities.
typedef uint32_t EntityID;

// used to identify types of components
typedef uint32_t ComponentTypeID;

// Shared pointer typedefs

class Entity;
typedef std::shared_ptr<Entity> StrongEntityPtr;
typedef std::weak_ptr<Entity> WeakEntityPtr;

class Component;
typedef std::shared_ptr<Component> StrongComponentPtr;
typedef std::weak_ptr<Component> WeakComponentPtr;