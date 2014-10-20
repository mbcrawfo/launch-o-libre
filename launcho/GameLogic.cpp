#include "GameLogic.h"
#include "utility/Timer.h"
#include <cassert>

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

void GameLogic::addEntity(StrongEntityPtr entity)
{
  assert(entities.find(entity->getID) == entities.end());
  entities[entity->getID()] = entity;
  // TODO: trigger new entity event
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
