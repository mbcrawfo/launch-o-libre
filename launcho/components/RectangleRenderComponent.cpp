#include "RectangleRenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "utility/conversions.h"

RectangleRenderComponent::RectangleRenderComponent(StrongEntityPtr parent)
:RenderComponent(parent)
{
}

bool RectangleRenderComponent::initialize()
{
  // sfml defaults the origin of an object to its upper left corner,
  // need to move that origin to the center of the object
  auto transform = parent->getComponent<TransformComponent>().lock();
  Vector2 origin = transform->getPosition() - transform->getUpperLeftCorner();
  rect.setSize(convert(transform->getBounds().halfSize * 2.0f));
  rect.setOrigin(convert(origin));
  return true;
}

void RectangleRenderComponent::draw(sf::RenderTarget& tgt)
{
  auto transform = parent->getComponent<TransformComponent>().lock();
  rect.setRotation(transform->getRotation());

  sf::Vector2f pos = convert(transform->getPosition());
  rect.setPosition(pos.x, 600.0f - pos.y);  

  tgt.draw(rect);
}

const sf::Color& RectangleRenderComponent::getColor() const
{
  return rect.getFillColor();
}

void RectangleRenderComponent::setColor(const sf::Color& color)
{
  rect.setFillColor(color);
}