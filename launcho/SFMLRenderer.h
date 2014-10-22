#pragma once

#include "IRenderSystem.h"
#include "types.h"
#include "components/RenderComponent.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>

class SFMLRenderer
  : public IRenderSystem
{
private:
  static const std::string TAG;

  std::shared_ptr<sf::RenderWindow> window;
  std::unordered_map<EntityID, StrongRenderComponentPtr> renderables;
  EventCallbackID addedCallbackID;
  EventCallbackID removedCallbackID;

public:
  SFMLRenderer() = delete;

  explicit SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window);

  virtual void initialize();
  virtual void update(const float deltaMs);
  virtual void destroy();

private:
  void entityAdded(StrongEventPtr evt);
  void entityRemoved(StrongEventPtr evt);
};