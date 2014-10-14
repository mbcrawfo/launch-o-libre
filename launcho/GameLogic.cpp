#include "GameLogic.h"
#include "utility/Timer.h"

const int MAX_EVENT_TIME = 5;

void GameLogic::initialize()
{
}

void GameLogic::update(const float deltaMs)
{
  for (auto entity : entities)
  {
    entity.second->update(deltaMs);
  }
}

void GameLogic::destroy()
{
  for (auto entity : entities)
  {
    entity.second->destroy();
  }
  entities.clear();
}

WeakEntityPtr GameLogic::createSimpleEntity(const EntityType type,
                                            const Vector2& pos,
                                            const AABB2& size)
{
  // TODO: dump this whole method for a factory

  static EntityID currentID = Entity::INVALID_ID;

  currentID++;
  StrongEntityPtr entity(new Entity(currentID));
  // add transform component for pos
  // add physics component for size
  
  switch (type)
  {
  case EntityType::Player:
    // add blue render component for size
    break;

  case EntityType::Enemy:
    // add red render component for size
    break;

  case EntityType::Terrain:    
    // add green render component for size
    break;
  }

  entities[currentID] = entity;
  // TODO: trigger new entity event

  return entity;
}

WeakEntityPtr GameLogic::getEntity(const EntityID id) const
{
  auto itr = entities.find(id);
  if (itr != entities.end())
  {
    return itr->second;
  }
  else
  {
    return WeakEntityPtr();
  }
}

void GameLogic::removeEntity(const EntityID id)
{
  auto itr = entities.find(id);
  if (itr != entities.end())
  {
    // TODO: trigger an entity removed event
    itr->second->destroy();
    entities.erase(itr);
  }
}
