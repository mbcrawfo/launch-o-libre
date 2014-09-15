#include "Game.h"
#include "utility/Timer.h"
#include <SDL.h>
#include <thread>
#include <iostream>

// try to sustain 30 fps
float Game::MAX_FRAME_TIME = 1000.0f / 30.0f;

Game::Game(int argc, char* argv[])
  : args(argc), logic(nullptr), render(nullptr), physics(nullptr), 
    eventManager(nullptr)
{
  for (int i = 0; i < argc; i++)
  {
    args[i] = std::string(argv[i]);
  }
}

Game::~Game()
{
  delete logic;
  delete render;
  delete physics;
  delete eventManager;
}

void Game::run()
{
  // TODO: init logging system
  initialize();
  mainLoop();
  shutdown();
}

void Game::initialize()
{
  SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

  logic = new NullLogicSystem;
  render = new NullRenderSystem;
  physics = new NullPhysicsSystem;
  eventManager = new NullEventSystem;

  logic->initialize();
  render->initialize();
  physics->initialize();
  eventManager->initialize();
}

void Game::mainLoop()
{
  bool running = true;
  float fps = 0;
  float lastFrameTime = 0.0f;
  Timer timer;

  while (running)
  {
    timer.start();

    running = logic->update(lastFrameTime);
    render->update(lastFrameTime);
    physics->update(lastFrameTime);
    eventManager->update(MAX_FRAME_TIME - timer.elapsedMilliF());

    lastFrameTime = timer.elapsedMilliF();
    fps = lastFrameTime / 1000.0f;

    // prevent using 100% cpu
    if (lastFrameTime < MAX_FRAME_TIME)
    {
      std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
  }
}

void Game::shutdown()
{
  // tear down in reverse order of initialization
  eventManager->destroy();
  physics->destroy();
  render->destroy();
  logic->destroy();

  SDL_Quit();
}

