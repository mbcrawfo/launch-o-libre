#pragma once

#include "ILogicSystem.h"
#include "IRenderSystem.h"
#include "IPhysicsSystem.h"
#include "IEventSystem.h"
#include "utility/Singleton.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

/**
 * Encapsulates the systems that make up the game.
 */
class Game
  : public Singleton<Game>
{
  static const std::string TAG;
  // max desired time for a single frame
  static const float MAX_FRAME_TIME;

  // in ms
  float lastFrameTime;
  // in sec
  float gameTime;
  uint32_t frameCount;
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<ILogicSystem> logic;  
  std::shared_ptr<IPhysicsSystem> physics;
  std::shared_ptr<IRenderSystem> render;
  std::shared_ptr<IEventSystem> eventManager;

public:  
  ~Game();

  /**
   * Executes the game.
   */
  void run();

  // frame stats accessors
  float getlastFrameTime() const;
  float getFPS() const;

  float getGameTime() const;

  // systems accessors - DO NOT HOLD THESE POINTERS
  // these should always return a valid pointer
  sf::RenderWindow* getWindow();
  ILogicSystem* getLogicSystem();
  IPhysicsSystem* getPhysicsSystem();
  IRenderSystem* getRenderSystem();
  IEventSystem* getEventSystem();

private:
  friend class Singleton<Game>;
  Game();

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

  // TODO: replace with some kind of level loading or generating stuff
  // probably in logic
  void createEntities();
};