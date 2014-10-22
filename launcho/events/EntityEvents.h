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

// Signals that an entity has moved in the game world
class EntityMovedEvent
  : public Event
{
public:
  static const EventID ID = 0x257B5763;

  const EntityID entity;

  EntityMovedEvent(const EntityID entity);
  EventID getID() const override;
  std::string getName() const override;
};

// Signals that two entities have collided
class EntityCollisionEvent
  : public Event
{
  static const EventID ID = 0x20529961;

  const EntityID first;
  const EntityID second;

  EntityCollisionEvent(const EntityID first, const EntityID second);
  EventID getID() const override;
  std::string getName() const override;
};