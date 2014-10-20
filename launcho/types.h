#pragma once

#include <cstdint>
#include <memory>
#include <functional>

// Used to identify entities.
using EntityID = uint32_t;

// used to identify types of components
using ComponentID = uint32_t;

// used to identify entity types
using EventID = uint32_t;

// uniquely identifies callbacks so that they can be deleted
using EventCallbackID = uint32_t;

// Sets the rendering order of graphics objects
// 0 is closest to the camera, 255 is farthest away
enum class RenderLayer : uint8_t
{
  UI = 0,
  Player = 50,
  Enemies = 100,
  Scenery = 200,
  Background = 255
};

// Shared pointer typedefs

class Entity;
using StrongEntityPtr = std::shared_ptr<Entity>;
using WeakEntityPtr = std::weak_ptr<Entity>;

class Component;
using StrongComponentPtr = std::shared_ptr<Component>;
using WeakComponentPtr = std::weak_ptr<Component>;

class Event;
using StrongEventPtr = std::shared_ptr<Event>;
using WeakEventPtr = std::weak_ptr<Event>;

// event callback functions
using EventCallback = std::function<void(StrongEventPtr evt)>;