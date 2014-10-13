#pragma once

#include "IRenderSystem.h"
#include <SFML/Graphics.hpp>
#include <memory>

class SFMLRenderer
  : public IRenderSystem
{
private:
  std::shared_ptr<sf::RenderWindow> window;

public:
  SFMLRenderer() = delete;

  explicit SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window);

  virtual void initialize();
  virtual void update(const float deltaMs);
  virtual void destroy();
};