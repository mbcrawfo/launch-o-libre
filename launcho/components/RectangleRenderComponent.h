#pragma once

#include "RenderComponent.h"
#include "types.h"

class RectangleRenderComponent;
using StrongRectangleRenderComponentPtr = 
  std::shared_ptr<RectangleRenderComponent>;
using WeakRectangleRenderComponentPtr = std::weak_ptr<RectangleRenderComponent>;

class RectangleRenderComponent
  : public RenderComponent
{
private:
  sf::RectangleShape rect;

public:
  RectangleRenderComponent(StrongEntityPtr parent);

  bool initialize() override;
  void draw(sf::RenderTarget& tgt) override;

  const sf::Color& getColor() const;
  void setColor(const sf::Color& color);
};