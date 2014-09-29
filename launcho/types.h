#pragma once

#include <cstdint>
#include <memory>

// Used to identify objects.
typedef uint32_t ObjectID;

// used to identify types of components
typedef uint32_t ComponentTypeID;

// Shared point typedefs

class Object;
typedef std::shared_ptr<Object> StrongObjectPtr;
typedef std::weak_ptr<Object> WeakObjectPtr;

class IComponent;
typedef std::shared_ptr<IComponent> StrongComponentPtr;
typedef std::weak_ptr<IComponent> WeakComponentPtr;