#pragma once

#include "IEventSystem.h"
#include "utility/Timer.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>

class GameEventSystem
  : public IEventSystem
{
private:
  using EventQueue = std::deque<StrongEventPtr>;
  using Listener = std::pair<EventCallbackID, EventCallback>;
  using ListenerVect = std::vector<Listener>;
  using EventListenerMap = std::unordered_map<EventID, ListenerVect>;

  static const std::string TAG;

  Timer timer;
  std::shared_ptr<sf::Window> window;
  EventListenerMap listeners;
  EventQueue queues[2];
  int activeQueue;

public:
  GameEventSystem() = delete;

  GameEventSystem(std::shared_ptr<sf::Window> _window);

  virtual void initialize() override;
  virtual void update(const float maxMs) override;
  virtual void destroy() override;

  bool addListener(EventID evtID, EventCallbackID id,
                   EventCallback fn) override;
  bool removeListener(EventID evtID, EventCallbackID id,
                      EventCallback fn)  override;

  void triggerEvent(StrongEventPtr evt) const override;
  void queueEvent(StrongEventPtr evt) override;
  bool abortEvent(const EventID id) override;
  uint32_t abortAllEvents(const EventID id) override;

private:
  void processWindowEvents();
  void processQueue(const float maxMs);
};