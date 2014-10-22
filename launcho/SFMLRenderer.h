#pragma once

#include "IRenderSystem.h"
#include "types.h"
#include "components/RenderComponent.h"
#include "utility/Timer.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

class SFMLRenderer
  : public IRenderSystem
{
private:
  static const std::string TAG;

  std::shared_ptr<sf::RenderWindow> window;
  sf::View view;
  sf::RenderTexture renderTexture;
  Timer timer;
  std::unordered_map<EntityID, StrongRenderComponentPtr> renderables;
  std::vector<StrongRenderComponentPtr> sortedRenderables;
  bool needSortUpdate;
  EventCallbackID addedCallbackID;
  EventCallbackID removedCallbackID;

public:
  SFMLRenderer() = delete;

  explicit SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window);

  virtual void initialize();
  virtual void update(const float deltaMs);
  virtual void destroy();

private:
  void sortRenderables();

  // callbacks
  void entityAddedCallback(StrongEventPtr evt);
  void entityRemovedCallback(StrongEventPtr evt);
};