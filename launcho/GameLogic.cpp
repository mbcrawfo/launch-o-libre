#include "GameLogic.h"
#include "utility/Timer.h"
#include "Game.h"
#include "events/EntityEvents.h"
#include "utility/Log.h"
#include "Game.h"
#include "events/InputEvents.h"
#include "components/PhysicsComponent.h"
#include <cassert>
#include <functional>

const std::string GameLogic::TAG = "GameLogic";

void GameLogic::initialize()
{
  // attach callbacks
  auto evtMgr = Game::getInstance().getEventSystem();
  // it SHOULD be ok to recycle this id since it is being registered
  // on 4 different event types
  inputCallbackID = evtMgr->generateNextCallbackID();
  evtMgr->addListener(
    InputUpEvent::ID,
    inputCallbackID,
    std::bind(&GameLogic::inputCallback, this, std::placeholders::_1)
    );
  evtMgr->addListener(
    InputDownEvent::ID,
    inputCallbackID,
    std::bind(&GameLogic::inputCallback, this, std::placeholders::_1)
    );
  evtMgr->addListener(
    InputLeftEvent::ID,
    inputCallbackID,
    std::bind(&GameLogic::inputCallback, this, std::placeholders::_1)
    );
  evtMgr->addListener(
    InputRightEvent::ID,
    inputCallbackID,
    std::bind(&GameLogic::inputCallback, this, std::placeholders::_1)
    );
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
  Log::verbose(TAG, "Clearing %u entities", entities.size());
  while (!entities.empty())
  {
    removeEntity(entities.begin()->second->getID());
  }

  // detach callbacks
  auto evtMgr = Game::getInstance().getEventSystem();
  evtMgr->removeListener(InputUpEvent::ID, inputCallbackID);
  evtMgr->removeListener(InputDownEvent::ID, inputCallbackID);
  evtMgr->removeListener(InputLeftEvent::ID, inputCallbackID);
  evtMgr->removeListener(InputRightEvent::ID, inputCallbackID);
}

void GameLogic::addEntity(StrongEntityPtr entity)
{
  assert(entities.find(entity->getID()) == entities.end());
  entities[entity->getID()] = entity;
  Log::debug(TAG, "Added entity %u", entity->getID());

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
    Log::warning(TAG, "Tried to retrieve non existing entity %u", id);
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
    Log::debug(TAG, "Removed entity %u", id);
  }
  else
  {
    Log::warning(TAG, "Tried to retrieve non existing entity %u", id);
  }
}

WeakEntityPtr GameLogic::getPlayer()
{
  assert(entities.find(PLAYER_ID) != entities.end());
  return entities[PLAYER_ID];
}

void GameLogic::inputCallback(StrongEventPtr evt)
{
  auto player = entities[PLAYER_ID];
  auto physics = player->getComponent<PhysicsComponent>().lock();

  switch (evt->getID())
  {
  case InputUpEvent::ID:
    physics->setAcceleration(Vector2(0.0f, 10.0f));
    break;

  case InputDownEvent::ID:
    physics->setAcceleration(Vector2(0.0f, -10.0f));
    break;

  case InputLeftEvent::ID:
    physics->setAcceleration(Vector2(-10.0f, 0.0f));
    break;

  case InputRightEvent::ID:
    physics->setAcceleration(Vector2(10.0f, 0.0f));
    break;

  default:
    Log::warning(
      TAG,
      "Unknown input event %08x (%s)",
      evt->getID(),
      evt->getNameC()
      );
  }
}
