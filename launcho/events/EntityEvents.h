#pragma once

#include "Event.h"

// Signals that an entity has been added to the game
class EntityAddedEvent
  : public Event
{
public:
  static const EventID ID = 0x430D9BB0;

  const EntityID entity;

  EntityAddedEvent(const EntityID entity);
  EventID getID() const override;
  std::string getName() const override;
};

// Signals that an entity is being removed from the game.
class EntityRemovedEvent
  : public Event
{
public:
  static const EventID ID = 0x85B3732C;

  const EntityID entity;

  EntityRemovedEvent(const EntityID entity);
  EventID getID() const override;
  std::string getName() const override;
};