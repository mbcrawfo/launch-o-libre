#include "InputEvents.h"

EventID InputUpEvent::getID() const
{
  return ID;
}

const char* InputUpEvent::getNameC() const
{
  return "InputUpEvent";
}

EventID InputDownEvent::getID() const
{
  return ID;
}

const char* InputDownEvent::getNameC() const
{
  return "InputDownEvent";
}

EventID InputLeftEvent::getID() const
{
  return ID;
}

const char* InputLeftEvent::getNameC() const
{
  return "InputLeftEvent";
}

EventID InputRightEvent::getID() const
{
  return ID;
}

const char* InputRightEvent::getNameC() const
{
  return "InputRightEvent";
}
