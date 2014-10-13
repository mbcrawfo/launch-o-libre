#pragma once

#include "IEventSystem.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GameEventSystem
  : public IEventSystem
{
private:
  std::shared_ptr<sf::Window> window;

public:
  GameEventSystem() = delete;

  GameEventSystem(std::shared_ptr<sf::Window> _window);

  virtual void initialize() override;
  virtual void update(const float maxMs) override;
  virtual void destroy() override;
};