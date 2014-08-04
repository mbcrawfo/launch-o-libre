#pragma once

#include <windows.h>
#include <cstdint>

/**
 * Timer that uses the windows high performance clock.
 */
class Timer final
{
private:
  static LARGE_INTEGER frequency;

  LARGE_INTEGER startTime;
  LARGE_INTEGER endTime;
  bool running;

public:
  // constructors
  explicit Timer(bool active = false);
  Timer(const Timer& copy);
  Timer& operator=(const Timer& rhs);

  /**
   * Start the timer. Resets the timer if it is running.
   */
  void start();

  /**
   * Stops the timer. Has no effect unless the timer is running.
   */
  void stop();

  /**
   * Resets the timer to an unused state.
   */
  void reset();

  /**
   * Returns the time since start() was called, in microseconds. If the timer 
   * is stopped, returns the time that elapsed between calls to start() and 
   * stop(). Overflows after ~584000 years.
   */
  uint64_t elapsedMicro();

  /**
   * Same behavior as elapsedMicro(), but returns the time in milliseconds. 
   * Overflow after ~49 days.
   */
  uint32_t elapsedMilli();

  /**
   * Same behavior as elapsedMicro(), but returns the time in floating point 
   * milliseconds.
   */
  float elapsedMilliF();

  /**
   * Same behavior as elapsedMicro(), but returns the time in seconds.
   */
  float elapsedSec();

private:
  /**
   * Updates the ending time of the timer.
   */
  void updateTime();
};