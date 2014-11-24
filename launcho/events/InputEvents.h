#pragma once

#include "Event.h"

enum class InputAction
{
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Fire
};

enum class InputActionState
{
  Invalid,
  Start,
  Stop
};

// Player input actions
class InputEvent
  : public Event
{
public:
  static const EventID ID = 0x813BA703;

  const InputAction action;
  const InputActionState state;

  InputEvent(InputAction action, 
             InputActionState state = InputActionState::Invalid);

  EventID getID() const override;
  const char* getNameC() const override;
};