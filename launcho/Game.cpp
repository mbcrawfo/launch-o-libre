#include "Game.h"
#include "utility/Timer.h"
#include "SFMLRenderer.h"
#include "GameLogic.h"
#include "GameEventSystem.h"
#include "utility/Log.h"
#include <thread>
#include <iostream>

const std::string Game::TAG = "Game";

// try to sustain 30 fps
const float Game::MAX_FRAME_TIME = 1000.0f / 30.0f;

Game::Game()
  : window(new sf::RenderWindow),
    logic(new GameLogic),
    render(new SFMLRenderer(window)),
    physics(new NullPhysicsSystem),
    eventManager(new GameEventSystem(window))
{
}

Game::~Game()
{
}

void Game::run()
{
  initialize();
  mainLoop();
  shutdown();
}

void Game::initialize()
{
  Log::verbose(TAG, "initialize start");
  logic->initialize();
  render->initialize();
  physics->initialize();
  eventManager->initialize();
  Log::verbose(TAG, "initialize complete");
}

void Game::mainLoop()
{
  Log::verbose(TAG, "main loop start");

  float fps = 0.0f;
  float lastFrameTime = 0.0f;
  Timer timer;

  while (window->isOpen())
  {
    timer.start();

    logic->update(lastFrameTime);
    render->update(lastFrameTime);
    physics->update(lastFrameTime);
    eventManager->update(MAX_FRAME_TIME - timer.elapsedMilliF());

    lastFrameTime = timer.elapsedMilliF();
    fps = 1000.0f / lastFrameTime;
    
    // prevent using 100% cpu
    if (lastFrameTime < MAX_FRAME_TIME)
    {
      std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
  }
}

void Game::shutdown()
{
  Log::verbose(TAG, "shutdown begin");
  // tear down in reverse order of initialization
  eventManager->destroy();
  physics->destroy();
  render->destroy();
  logic->destroy();
  Log::verbose(TAG, "shutdown complete");
}

