#include "SFMLRenderer.h"
#include "options.h"
#include "GameOptions.h"
#include <string>
#include <cassert>

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> _window)
: window(_window)
{
  assert(window.get() != nullptr);
}

void SFMLRenderer::initialize()
{
  int width = GameOptions::getInstance().getInt(SCREEN_WIDTH);
  int height = GameOptions::getInstance().getInt(SCREEN_HEIGHT);
  std::string title = GameOptions::getInstance().getString(WINDOW_TITLE);

  window->create(
    sf::VideoMode(width, height),
    title,
    sf::Style::Titlebar | sf::Style::Close
    );
}

void SFMLRenderer::update(const float deltaMs)
{
  window->clear();
  window->display();
}

void SFMLRenderer::destroy()
{
}
