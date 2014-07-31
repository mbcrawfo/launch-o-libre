#include "utility/Timer.h"

LARGE_INTEGER Timer::frequency;

Timer::Timer(bool active)
  : startTime(), endTime(), running(false)
{
  if (active)
  {
    start();
  }
}

Timer::Timer(const Timer& copy)
  : startTime(copy.startTime), endTime(copy.endTime), running(copy.running)
{}

Timer& Timer::operator=(const Timer& rhs)
{
  startTime = rhs.startTime;
  endTime = rhs.endTime;
  running = rhs.running;
  return *this;
}

void Timer::start()
{
  QueryPerformanceCounter(&startTime);
  running = true;
}

void Timer::stop()
{
  if (running)
  {
    updateTime();
    running = false;
  }
}

void Timer::reset()
{
  *this = Timer();
}

uint64_t Timer::elapsedMicro()
{
  if (running)
  {
    updateTime();
  }
  if (frequency.QuadPart == 0)
  {
    QueryPerformanceFrequency(&frequency);
  }

  auto elapsed = endTime.QuadPart - startTime.QuadPart;
  // convert to us now so precision isn't lost in division
  elapsed *= 1000000;
  return elapsed / frequency.QuadPart;
}

uint32_t Timer::elapsedMilli()
{
  return (int32_t)(elapsedMicro() / 1000);
}

float Timer::elapsedSec()
{
  return elapsedMicro() / 1000000.0f;
}

void Timer::updateTime()
{
  QueryPerformanceCounter(&endTime);
}
