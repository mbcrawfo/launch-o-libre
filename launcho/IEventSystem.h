#pragma once

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

  // TODO: event specific methods...
};