#pragma once

#include "Component.h"
#include "types.h"
#include <SFML/Graphics.hpp>

class RectangleRenderComponent
  : public Component
{
private:
  sf::RectangleShape rect;

public:
  static const ComponentTypeID ID = 0xd29cfdfb;

  RectangleRenderComponent(StrongEntityPtr _parent);

  ComponentTypeID getID() const override;
  bool initialize() override;
  void destroy() override;

};