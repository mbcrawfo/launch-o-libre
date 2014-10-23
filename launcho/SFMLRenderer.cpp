#include "SFMLRenderer.h"
#include "options.h"
#include "GameOptions.h"
#include "Game.h"
#include "Entity.h"
#include "components/PhysicsComponent.h"
#include "events/EntityEvents.h"
#include "utility/Log.h"
#include <string>
#include <cassert>
#include <functional>
#include <cstdio>

const std::string SFMLRenderer::TAG = "SFMLRenderer";

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window)
: window(_window),
  view(),
  renderTexture(),
  timer(),
  renderables(),
  sortedRenderables(),
  needSortUpdate(false),
  font(),
  addedCallbackID(0),
  removedCallbackID(0)
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

  // create the view
  view.setSize(sf::Vector2f((float)width, (float)height));
  view.setViewport(sf::FloatRect(0, 0, 1, 1));
  view.setCenter(width / 2.0f, height / 2.0f);

  // and the target texture
  if (!renderTexture.create(width, height))
  {
    Log::error(TAG, "Unable to create render texture");
  }
  renderTexture.setView(view);

  // load font for UI
  if (!font.loadFromFile("data/fonts/arial.ttf"))
  {
    Log::error(TAG, "Could not load arial font");
  }

  // event registration
  auto evtMgr = Game::getInstance().getEventSystem();
  addedCallbackID = evtMgr->generateNextCallbackID();
  evtMgr->addListener(
    EntityAddedEvent::ID,
    addedCallbackID,
    std::bind(&SFMLRenderer::entityAddedCallback, this, std::placeholders::_1)
    );
  removedCallbackID = evtMgr->generateNextCallbackID();
  evtMgr->addListener(
    EntityRemovedEvent::ID,
    removedCallbackID,
    std::bind(&SFMLRenderer::entityRemovedCallback, this, std::placeholders::_1)
    );
}

void SFMLRenderer::update(const float deltaMs)
{
  timer.start(); 

  // TODO update view pos as the player moves
  renderTexture.setView(view);
  window->setView(view);

  renderTexture.clear(sf::Color::White);  

  sortRenderables();
  for (auto rc : sortedRenderables)
  {
    rc->draw(renderTexture);
  }

  drawUI();
  renderTexture.display();
  window->draw(sf::Sprite(renderTexture.getTexture()));

  // HACK: SFML 2.1 is a piece of shit and doesn't clear correctly on certain
  // gfx cards... supposed to be fixed in 2.2
  // For whatever reason drawing this transparent rectangle fixes it
  sf::RectangleShape shape(sf::Vector2f(0, 0));
  shape.setFillColor(sf::Color(0, 0, 0, 0));
  window->draw(shape);

  window->display();
  Log::verbose(TAG, "Rendering complete in %.2fms", timer.elapsedMilliF());
}

void SFMLRenderer::destroy()
{
  auto evtMgr = Game::getInstance().getEventSystem();
  evtMgr->removeListener(EntityAddedEvent::ID, addedCallbackID);
  evtMgr->removeListener(EntityRemovedEvent::ID, removedCallbackID);
}

void SFMLRenderer::sortRenderables()
{
  if (needSortUpdate)
  {
    auto sorter = 
      [](StrongRenderComponentPtr rc1, StrongRenderComponentPtr rc2) {
        // sort in reverse order
        return rc1->getLayer() > rc2->getLayer();
    };

    std::sort(
      sortedRenderables.begin(),
      sortedRenderables.end(),
      sorter
      );
    needSortUpdate = false;
  }
}

void SFMLRenderer::drawUI()
{
  auto player = Game::getInstance().getLogicSystem()->getPlayer().lock();
  assert(player != nullptr);
  auto physics = player->getComponent<PhysicsComponent>().lock();
  assert(physics != nullptr);
  Vector2 vel = physics->getVelocity();

  char buffer[32];
  sprintf_s(buffer, 32, "Velocity <%01.2f, %01.2f>", vel.x, vel.y);
  sf::Text text(buffer, font, 18);
  text.setPosition(10.0f, 10.0f);
  text.setColor(sf::Color::Black);

  renderTexture.draw(text);
}

void SFMLRenderer::entityAddedCallback(StrongEventPtr evt)
{
  auto eae = Event::cast<EntityAddedEvent>(evt);
  if (eae == nullptr)
  {
    Log::error(
      TAG,
      "Couldn't cast to EntityAddedEvent, type %u (%s)",
      evt->getID(),
      evt->getNameC()
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
      sortedRenderables.push_back(rc);
      needSortUpdate = true;
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

void SFMLRenderer::entityRemovedCallback(StrongEventPtr evt)
{
  auto ere = Event::cast<EntityRemovedEvent>(evt);
  if (ere == nullptr)
  {
    Log::error(
      TAG,
      "Couldn't cast to EntityRemovedEvent, type %u (%s)",
      evt->getID(),
      evt->getNameC()
      );
    return;
  }

  auto itr = renderables.find(ere->entity);
  if (itr != renderables.end())
  {
    renderables.erase(itr);

    // is it cheaper to swap & pop then resort?
    auto itr2 = std::find_if(
      sortedRenderables.begin(),
      sortedRenderables.end(),
      [&](StrongRenderComponentPtr rc) {
        return rc->getParentID() == ere->entity;
      }
      );
    assert(itr2 != sortedRenderables.end());
    sortedRenderables.erase(itr2);
  }
  else
  {
    Log::debug(TAG, "Entity %u not found in renderable list", ere->entity);
  }
}
