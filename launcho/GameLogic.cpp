#include "GameLogic.h"
#include "utility/Timer.h"
#include <SDL.h>

const int MAX_EVENT_TIME = 5;

void GameLogic::initialize()
{
}

bool GameLogic::update(const float deltaMs)
{
  return processEvents();
}

void GameLogic::destroy()
{
}

bool GameLogic::processEvents()
{
  SDL_Event event;
  Timer timer;

  while (SDL_PollEvent(&event) && timer.elapsedMilli() < MAX_EVENT_TIME)
  {
    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
    {
      return false;
    }
  }

  return true;
}
