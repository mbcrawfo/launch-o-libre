#include "GameEventSystem.h"
#include "utility/Log.h"
#include "events/Event.h"
#include <cassert>
#include <algorithm>

const std::string GameEventSystem::TAG = "GameEventSystem";

GameEventSystem::GameEventSystem(std::shared_ptr<sf::Window> window)
: timer(),
  window(window),
  listeners(),
  queues(),
  activeQueue(0)
{
  assert(window.get() != nullptr);
}

void GameEventSystem::initialize()
{
}

void GameEventSystem::update(const float maxMs)
{
  timer.start();
  processWindowEvents();
  processQueue(maxMs);
}

void GameEventSystem::destroy()
{
  queues[0].clear();
  queues[1].clear();
  listeners.clear();
}

bool GameEventSystem::addListener(EventID evtID, EventCallbackID id,
                                  EventCallback fn)
{
  auto itr = listeners.find(evtID);
  if (itr != listeners.end())
  {
    auto itr2 = std::find_if(
      itr->second.begin(), 
      itr->second.end(),
      [&] (const Listener& l) {
          return l.first == id;
        }
      );
      
    if (itr2 != itr->second.end())
    {
      Log::warning(
        TAG,
        "Attempt to double register callback %u to event type %u",
        id, 
        evtID
        );
      return false;
    }
  }

  listeners[evtID].push_back(std::make_pair(id, fn));
  Log::verbose(TAG, "Added listener %u for event type %u", id, evtID);
  return true;
}

bool GameEventSystem::removeListener(EventID evtID, EventCallbackID id,
                                     EventCallback fn)
{
  auto itr = listeners.find(id);
  if (itr != listeners.end())
  {
    auto itr2 = std::find_if(
      itr->second.begin(),
      itr->second.end(),
      [&](const Listener& l) {
          return l.first == id;
        }
      );
    if (itr2 != itr->second.end())
    {
      itr->second.erase(itr2);
      Log::verbose(
        TAG,
        "Removed listener %u for event type %u",
        id,
        evtID
        );
    }
    Log::warning(
      TAG,
      "Tried to remove listener for %u but it was not found", 
      id
      );
  }
  else
  {
    Log::warning(
      TAG, 
      "Tried to remove listener for %u but no listeners were registered",
      id
      );
  }

  return false;
}

void GameEventSystem::triggerEvent(StrongEventPtr evt) const
{
  assert(evt != nullptr);
  auto itr = listeners.find(evt->getID());
  if (itr != listeners.end())
  {
    for (auto listener : itr->second)
    {
      listener.second(evt);
    }
  }
}

void GameEventSystem::queueEvent(StrongEventPtr evt)
{
  assert(evt != nullptr);
  queues[activeQueue].push_back(evt);
}

bool GameEventSystem::abortEvent(const EventID id)
{
  auto itr = std::find_if(
    queues[activeQueue].begin(),
    queues[activeQueue].end(),
    [&](StrongEventPtr evt) {
      return evt->getID() == id;
    }
    );

  if (itr != queues[activeQueue].end())
  {
    queues[activeQueue].erase(itr);
    return true;
  }
  else
  {
    return false;
  }
}

uint32_t GameEventSystem::abortAllEvents(const EventID id)
{
  uint32_t count = queues[activeQueue].size();

  std::remove_if(
    queues[activeQueue].begin(),
    queues[activeQueue].end(),
    [&](StrongEventPtr evt) {
      return evt->getID() == id;
    }
    );

  return count - queues[activeQueue].size();
}

void GameEventSystem::processWindowEvents()
{
  sf::Event evt;

  while (window->pollEvent(evt))
  {
    if (evt.type == sf::Event::Closed)
    {
      window->close();
      return;
    }
  }
}

void GameEventSystem::processQueue(const float maxMs)
{
  EventQueue& q = queues[activeQueue];
  // flip the queues so that any new events generated during event processing
  // are sent to the new queue
  activeQueue = (activeQueue + 1) & 1;

  while (!q.empty())
  {
    StrongEventPtr evt = q.front();
    q.pop_front();

    auto itr = listeners.find(evt->getID());
    if (itr != listeners.end())
    {
      for (auto listener : itr->second)
      {
        listener.second(evt);
      }
    }

    if (timer.elapsedMilliF() > maxMs)
    {
      Log::warning(
        TAG,
        "Event processing aborted after %.2fms, %u events remaining",
        timer.elapsedMilliF(),
        q.size()
        );

      // copy remaining events to the start of the current queue
      std::copy(q.begin(), q.end(), queues[activeQueue].begin());
      q.clear();
    }
  }
}