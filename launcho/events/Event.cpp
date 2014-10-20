#include "Event.h"

const std::string Event::TAG = "Event";

Event::Event(const float _timestamp)
:timestamp(_timestamp)
{
}

float Event::getTimestamp() const
{
  return timestamp;
}