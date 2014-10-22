#include "InputEvents.h"

EventID InputUpEvent::getID() const
{
  return ID;
}

const char* InputUpEvent::getName() const
{
  return "InputUpEvent";
}

EventID InputDownEvent::getID() const
{
  return ID;
}

const char* InputDownEvent::getName() const
{
  return "InputDownEvent";
}

EventID InputLeftEvent::getID() const
{
  return ID;
}

const char* InputLeftEvent::getName() const
{
  return "InputLeftEvent";
}

EventID InputRightEvent::getID() const
{
  return ID;
}

const char* InputRightEvent::getName() const
{
  return "InputRightEvent";
}
