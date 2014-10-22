#pragma once

#include "types.h"

class IEventSystem
{
public:
  virtual ~IEventSystem() = default;

  /**
   * Initializes the event manager system. Should use exceptions to signal 
   * failure.
   */
  virtual void initialize() = 0;

  /**
   * Updates the event manager.
   * @param maxMs[in] The maximum amount of time that can be spent processing 
   * events.
   */
  virtual void update(const float maxMs) = 0;

  /**
   * Tears down the event system.
   */
  virtual void destroy() = 0;

  // generate a new id to uniquely identify a callback
  virtual EventCallbackID generateNextCallbackID() = 0;

  // adds a callback listening for the specific event type
  // generate a new guid for each callback so that it can be removed
  virtual bool addListener(EventID evtID, EventCallbackID callbackID,
                           EventCallback fn) = 0;

  // searches for a stored listener and removes it
  virtual bool removeListener(EventID evtID, EventCallbackID callbackID) = 0;

  // immediately fires an event without using the queue
  virtual void triggerEvent(StrongEventPtr evt) const = 0;

  // adds an event to the queue for later processing
  virtual void queueEvent(StrongEventPtr evt) = 0;

  // finds the first event of the type and removes it from the queue
  // returns true if successful
  virtual bool abortEvent(const EventID id) = 0;

  // aborts all events of the type
  // returns the number of events aborted
  virtual uint32_t abortAllEvents(const EventID id) = 0;
};