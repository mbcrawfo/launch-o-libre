#include "GameEventSystem.h"
#include "utility/Timer.h"
#include <cassert>

GameEventSystem::GameEventSystem(std::shared_ptr<sf::Window> _window)
: window(_window)
{
  assert(window.get() != nullptr);
}

void GameEventSystem::initialize()
{
}

void GameEventSystem::update(const float maxMs)
{
  Timer timer;
  sf::Event event;

  timer.start();
  while (window->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window->close();
      return;
    }
  }
}

void GameEventSystem::destroy()
{
}
