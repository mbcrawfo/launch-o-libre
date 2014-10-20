#include "GameLogic.h"
#include "utility/Timer.h"
#include "Game.h"
#include "events/EntityEvents.h"
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
  assert(entities.find(entity->getID()) == entities.end());
  entities[entity->getID()] = entity;
  
  StrongEventPtr evt(new EntityAddedEvent(entity->getID()));
  Game::getInstance().getEventSystem()->queueEvent(evt);
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
    // this event needs to be triggered immediately so that systems can
    // respond to it before the entity is gone
    StrongEventPtr evt(new EntityRemovedEvent(itr->second->getID()));
    Game::getInstance().getEventSystem()->triggerEvent(evt);
    
    itr->second->destroy();
    entities.erase(itr);
  }
}
