#pragma once

#include "ILogicSystem.h"
#include "IRenderSystem.h"
#include "IPhysicsSystem.h"
#include "IEventSystem.h"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * Encapsulates the systems that make up the game.
 */
class Game
{
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<ILogicSystem> logic;
  std::shared_ptr<IRenderSystem> render;
  std::shared_ptr<IPhysicsSystem> physics;
  std::shared_ptr<IEventSystem> eventManager;

public:
  // max desired time for a single frame
  static float MAX_FRAME_TIME;

  Game();
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  ~Game();

  void run();

private:
  void initialize();
  void mainLoop();
  void shutdown();
};