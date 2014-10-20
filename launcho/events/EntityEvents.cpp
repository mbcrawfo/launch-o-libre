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
