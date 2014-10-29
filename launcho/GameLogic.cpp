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
    InputEvent::ID,
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
  evtMgr->removeListener(InputEvent::ID, inputCallbackID);
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
  auto ie = Event::cast<InputEvent>(evt);

  if (ie == nullptr)
  {
    Log::warning(
      TAG,
      "Unknown input event %08x (%s)",
      evt->getID(),
      evt->getNameC()
      );
  }
  else
  {
    auto player = entities[PLAYER_ID];
    auto physics = player->getComponent<PhysicsComponent>().lock();

//     switch (ie->action)
//     {
//     case InputAction::MoveUp:
//       if (ie->state == InputActionState::Start)
//       {
//         physics->modAcceleration(Vector2::UNIT_Y * 20.0f);
//       }
//       else if (ie->state == InputActionState::Stop)
//       {
//         physics->modAcceleration(Vector2::UNIT_Y * -20.0f);
//       }
//       break;
// 
//     case InputAction::MoveDown:
//       if (ie->state == InputActionState::Start)
//       {
//         physics->modAcceleration(Vector2::UNIT_Y * -20.0f);
//       }
//       else if (ie->state == InputActionState::Stop)
//       {
//         physics->modAcceleration(Vector2::UNIT_Y * 20.0f);
//       }
//       break;
// 
//     case InputAction::MoveLeft:
//       if (ie->state == InputActionState::Start)
//       {
//         physics->modAcceleration(Vector2::UNIT_X * -20.0f);
//       }
//       else if (ie->state == InputActionState::Stop)
//       {
//         physics->modAcceleration(Vector2::UNIT_X * 20.0f);
//       }
//       break;
// 
//     case InputAction::MoveRight:
//       if (ie->state == InputActionState::Start)
//       {
//         physics->modAcceleration(Vector2::UNIT_X * 20.0f);
//       }
//       else if (ie->state == InputActionState::Stop)
//       {
//         physics->modAcceleration(Vector2::UNIT_X * -20.0f);
//       }
//       break;
//     }
  }
}
