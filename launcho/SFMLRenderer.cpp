#include "SFMLRenderer.h"
#include "options.h"
#include "GameOptions.h"
#include "Game.h"
#include "Entity.h"
#include "events/EntityEvents.h"
#include "utility/Log.h"
#include <string>
#include <cassert>
#include <functional>

const std::string SFMLRenderer::TAG = "SFMLRenderer";

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window)
: window(_window)
{
  assert(window != nullptr);
}

void SFMLRenderer::initialize()
{
  // window creation
  int width = GameOptions::getInstance().getInt(SCREEN_WIDTH);
  int height = GameOptions::getInstance().getInt(SCREEN_HEIGHT);
  std::string title = GameOptions::getInstance().getString(WINDOW_TITLE);
  window->create(
    sf::VideoMode(width, height),
    title,
    sf::Style::Titlebar | sf::Style::Close
    );
  Log::debug(TAG, "Window created, %dx%d", width, height);

  // event registration
  auto evtMgr = Game::getInstance().getEventSystem();
  addedCallbackID = evtMgr->generateNextCallbackID();
  evtMgr->addListener(
    EntityAddedEvent::ID,
    addedCallbackID,
    std::bind(&SFMLRenderer::entityAdded, this, std::placeholders::_1)
    );
  removedCallbackID = evtMgr->generateNextCallbackID();
  evtMgr->addListener(
    EntityRemovedEvent::ID,
    removedCallbackID,
    std::bind(&SFMLRenderer::entityRemoved, this, std::placeholders::_1)
    );
}

void SFMLRenderer::update(const float deltaMs)
{
  window->clear(sf::Color::White);
  for (auto item : renderables)
  {
    item.second->draw(*window);
  }
  window->display();
}

void SFMLRenderer::destroy()
{
  auto evtMgr = Game::getInstance().getEventSystem();
  evtMgr->removeListener(EntityAddedEvent::ID, addedCallbackID);
  evtMgr->removeListener(EntityRemovedEvent::ID, removedCallbackID);
}

void SFMLRenderer::entityAdded(StrongEventPtr evt)
{
  auto eae = Event::cast<EntityAddedEvent>(evt);
  if (eae == nullptr)
  {
    Log::error(
      TAG,
      "Couldn't cast to EntityAddedEvent, type %u (%s)",
      evt->getID(),
      evt->getName()
      );
    return;
  }

  auto entity = 
    Game::getInstance().getLogicSystem()->getEntity(eae->entity).lock();
  assert(entity != nullptr);

  auto rc = entity->getComponent<RenderComponent>().lock();
  if (rc != nullptr)
  {
    if (renderables.find(entity->getID()) != renderables.end())
    {
      Log::error(TAG, "Tried to add duplicate entity %u", entity->getID());
    }
    else
    {
      renderables[entity->getID()] = rc;
    }
  }
  else
  {
    Log::debug(
      TAG,
      "Ignoring add of non-renderable entity %u",
      entity->getID()
      );
  }
}
 

void SFMLRenderer::entityRemoved(StrongEventPtr evt)
{
  auto ere = Event::cast<EntityRemovedEvent>(evt);
  if (ere == nullptr)
  {
    Log::error(
      TAG,
      "Couldn't cast to EntityRemovedEvent, type %u (%s)",
      evt->getID(),
      evt->getName()
      );
    return;
  }

  auto entity =
    Game::getInstance().getLogicSystem()->getEntity(ere->entity).lock();
  assert(entity != nullptr);

  auto itr = renderables.find(entity->getID());
  if (itr != renderables.end())
  {
    renderables.erase(itr);
  }
  else
  {
    Log::debug(TAG, "Entity %u not found in renderable list", entity->getID());
  }
}
