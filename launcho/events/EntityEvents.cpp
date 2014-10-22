#include "EntityEvents.h"

EntityAddedEvent::EntityAddedEvent(const EntityID entity)
:Event(), entity(entity)
{
}

EventID EntityAddedEvent::getID() const
{
  return ID;
}

std::string EntityAddedEvent::getName() const
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

std::string EntityRemovedEvent::getName() const
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

std::string EntityMovedEvent::getName() const
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

std::string EntityCollisionEvent::getName() const
{
  return "EntityCollisionEvent";
}
