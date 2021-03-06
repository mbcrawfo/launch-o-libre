#pragma once

#include "Component.h"
#include "types.h"
#include <SFML/Graphics.hpp>

class RenderComponent;
using StrongRenderComponentPtr = std::shared_ptr<RenderComponent>;
using WeakRenderComponentPtr = std::weak_ptr<RenderComponent>;

/**
 * The base for all rendering components.  This is sub classed to implement a
 * specific type of render, but only this class has a unique id.
 * tl;dr If you want to get a rendering component out of an entity you need to 
 * call entity.getComponent<RenderComponent>() and then cast it.
 */
class RenderComponent
  : public Component
{
private:
  RenderLayer layer;

public:
  static const ComponentID ID = 0xd29cfdfb;

  explicit RenderComponent(StrongEntityPtr _parent, 
                           RenderLayer _layer = RenderLayer::Background);

  ComponentID getID() const override final;

  RenderLayer getLayer() const;
  void setLayer(RenderLayer newLayer);

  // Draws the component onto a render target
  virtual void draw(sf::RenderTarget& tgt) = 0;
};