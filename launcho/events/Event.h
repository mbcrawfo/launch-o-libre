#pragma once

#include "types.h"
#include "utility/Log.h"
#include <string>
#include <cassert>

// The base for all events.
class Event
{
private:
  static const std::string TAG;

  const float timestamp;

public:
  template<typename EventType>
  static std::shared_ptr<EventType> cast(StrongEventPtr evt);

  Event();
  Event& operator=(Event&) = delete;

  virtual ~Event() = default;

  float getTimestamp() const;

  // get info about the event type
  virtual EventID getID() const = 0;
  virtual const char* getNameC() const = 0;
  const std::string getName() const;
};

template<typename EventType>
std::shared_ptr<EventType> Event::cast(StrongEventPtr evt)
{
  assert(evt != nullptr);

  if (evt->getID() == EventType::ID)
  {
    return std::dynamic_pointer_cast<EventType>(evt);
  }
  else
  {
    Log::warning(TAG,
                 "Invalid pointer cast, expected %u, type was %u (%s)",
                 EventType::ID, 
                 evt->getID(), 
                 evt->getNameC()
                 );
    return std::shared_ptr<EventType>();
  }
}