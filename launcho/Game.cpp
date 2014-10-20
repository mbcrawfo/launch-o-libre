#include "Game.h"
#include "utility/Timer.h"
#include "SFMLRenderer.h"
#include "GameLogic.h"
#include "GameEventSystem.h"
#include "utility/Log.h"
#include "events/EntityEvents.h"
#include <thread>
#include <iostream>

const std::string Game::TAG = "Game";

// try to sustain 30 fps
const float Game::MAX_FRAME_TIME = 1000.0f / 30.0f;

Game::Game()
  : gameTime(0.0f),
    lastFrameTime(0.0f),
    window(new sf::RenderWindow),
    logic(new GameLogic),    
    physics(new NullPhysicsSystem),
    render(new SFMLRenderer(window)),
    eventManager(new GameEventSystem(window))
{
}

Game::~Game()
{
}

float Game::getlastFrameTime() const
{
  return lastFrameTime;
}

float Game::getFPS() const
{
  return 1000.0f / lastFrameTime;
}

float Game::getGameTime() const
{
  return gameTime;
}

sf::RenderWindow* Game::getWindow()
{
  return window.get();
}

ILogicSystem* Game::getLogicSystem()
{
  return logic.get();
}

IPhysicsSystem* Game::getPhysicsSystem()
{
  return physics.get();
}

IRenderSystem* Game::getRenderSystem()
{
  return render.get();
}

IEventSystem* Game::getEventSystem()
{
  return eventManager.get();
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
  physics->initialize();
  render->initialize();
  eventManager->initialize();
  Log::verbose(TAG, "initialize complete");
}

void Game::mainLoop()
{
  Log::verbose(TAG, "main loop start");
  Timer timer;

  while (window->isOpen())
  {
    timer.start();

    logic->update(lastFrameTime);    
    physics->update(lastFrameTime);
    render->update(lastFrameTime);
    eventManager->update(MAX_FRAME_TIME - timer.elapsedMilliF());
    lastFrameTime = timer.elapsedMilliF();
    gameTime += lastFrameTime / 1000.0f;
    
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
  render->destroy();
  physics->destroy();  
  logic->destroy();
  Log::verbose(TAG, "shutdown complete");
}


