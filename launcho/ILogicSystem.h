#pragma once

class ILogicSystem
{
public:
  virtual ~ILogicSystem() = default;

  /**
   * Initializes the game logic system. Should use exceptions to signal failure.
   */
  virtual void initialize() = 0;

  /**
   * Updates the game logic.
   * @param deltaMs The elapsed time since the last frame.
   */
  virtual void update(const float deltaMs) = 0;

  /**
   * Tears down the physics system.
   */
  virtual void destroy() = 0;
};

/**
 * Logic system that does nothing.
 */
class NullLogicSystem
  : public ILogicSystem
{
public:
  virtual void initialize() override {}
  virtual void update(const float deltaMs) override 
  {
    (void) deltaMs;
  }
  virtual void destroy() override {}
};