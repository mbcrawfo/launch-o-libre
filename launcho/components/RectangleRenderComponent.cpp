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
  auto tc = parent->getComponent<TransformComponent>().lock();
  Vector2 origin = tc->getPosition() - tc->getUpperLeftCorner();
  rect.setSize(convert(tc->getBounds().halfSize * 2.0f));
  rect.setOrigin(convert(tc->getBounds().halfSize));
  return true;
}

void RectangleRenderComponent::draw(sf::RenderTarget& tgt)
{
  auto tc = parent->getComponent<TransformComponent>().lock();
  sf::Transform transform;
  transform.translate(
    tc->getPosition().x,
    // SFML uses an inverted y axis, need to account for that
    tgt.getSize().y - tc->getPosition().y
    );
  transform.rotate(tc->getRotation());
  tgt.draw(rect, transform);
}

const sf::Color& RectangleRenderComponent::getColor() const
{
  return rect.getFillColor();
}

void RectangleRenderComponent::setColor(const sf::Color& color)
{
  rect.setFillColor(color);
}