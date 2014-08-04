#pragma once

#include "ILogicSystem.h"
#include "IRenderSystem.h"
#include "IPhysicsSystem.h"
#include "IEventSystem.h"
#include <string>
#include <vector>

/**
 * Encasulates the systems that make up the game.
 */
class Game
{
  std::vector<std::string> args;
  ILogicSystem* logic;
  IRenderSystem* render;
  IPhysicsSystem* physics;
  IEventSystem* eventManager;

public:
  // max desired time for a single frame
  static float MAX_FRAME_TIME;

  Game() = delete;
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  Game(int argc, char* argv[]);
  ~Game();

  void run();

private:
  void initialize();
  void mainLoop();
  void shutdown();
};