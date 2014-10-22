#include "EntityEvents.h"

EntityAddedEvent::EntityAddedEvent(const EntityID entity)
:Event(), entity(entity)
{
}

EventID EntityAddedEvent::getID() const
{
  return ID;
}

const char* EntityAddedEvent::getNameC() const
{
  return "EntityAddedEvent";
}

EntityRemovedEvent::EntityRemovedEvent(const EntityID entity)
: Event(), entity(entity)
{
}

EventID EntityRemovedEvent::getID() const
{
  return ID;
}

const char* EntityRemovedEvent::getNameC() const
{
  return "EntityRemovedEvent";
}

EntityMovedEvent::EntityMovedEvent(const EntityID entity)
: entity(entity)
{
}

EventID EntityMovedEvent::getID() const
{
  return ID;
}

const char* EntityMovedEvent::getNameC() const
{
  return "EntityMovedEvent";
}

EntityCollisionEvent::EntityCollisionEvent(const EntityID first, 
                                           const EntityID second)
: first(first), second(second)
{
}

EventID EntityCollisionEvent::getID() const
{
  return ID;
}

const char* EntityCollisionEvent::getNameC() const
{
  return "EntityCollisionEvent";
}
