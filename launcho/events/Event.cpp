#include "Event.h"
#include "Game.h"

const std::string Event::TAG = "Event";

Event::Event()
:timestamp(Game::getInstance().getGameTime())
{
}

float Event::getTimestamp() const
{
  return timestamp;
}

const std::string Event::getName() const
{
  return getNameC();
}
