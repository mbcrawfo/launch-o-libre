#pragma once

#include "Event.h"

// Keyboard input that moves the player up
class InputUpEvent
  : public Event
{
public:
  static const EventID ID = 0x813BA703;

  EventID getID() const override;
  const char* getNameC() const override;
};

// Keyboard input that moves the player down
class InputDownEvent
  : public Event
{
public:
  static const EventID ID = 0xA6B8E5D0;

  EventID getID() const override;
  const char* getNameC() const override;
};

// Keyboard input that moves the player left
class InputLeftEvent
  : public Event
{
public:
  static const EventID ID = 0x51C0A6B3;

  EventID getID() const override;
  const char* getNameC() const override;
};

// Keyboard input that moves the player right
class InputRightEvent
  : public Event
{
public:
  static const EventID ID = 0x8144BB8A;

  EventID getID() const override;
  const char* getNameC() const override;
};