#include "InputEvents.h"

InputEvent::InputEvent(InputAction action, InputActionState state)
  : action(action), state(state)
{
}

EventID InputEvent::getID() const
{
  return ID;
}

const char* InputEvent::getNameC() const
{
  return "InputEvent";
}
