#pragma once

#include "ILogicSystem.h"
#include "IRenderSystem.h"
#include "IPhysicsSystem.h"
#include "IEventSystem.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

/**
 * Encapsulates the systems that make up the game.
 */
class Game
{
  static const std::string TAG;
  // max desired time for a single frame
  static const float MAX_FRAME_TIME;

  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<ILogicSystem> logic;
  std::shared_ptr<IRenderSystem> render;
  std::shared_ptr<IPhysicsSystem> physics;
  std::shared_ptr<IEventSystem> eventManager;

public:
  // prevent copying
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  
  Game();
  ~Game();

  /**
   * Executes the game.
   */
  void run();

private:
  /**
   * Init all sub systems of the game.
   */
  void initialize();

  /**
   * Perform the main logic/render loop.
   */
  void mainLoop();

  /**
   * Clean up resources.
   */
  void shutdown();
};