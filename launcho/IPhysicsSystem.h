#pragma once

class IPhysicsSystem
{
public:
  virtual ~IPhysicsSystem() = default;

  /**
   * Initializes the physics system. Should use exceptions to signal failure.
   */
  virtual void initialize() = 0;

  /**
   * Updates the phsyics system.
   * @param[in] deltaMs The elapsed time since the last frame.
   */
  virtual void update(const float deltaMs) = 0;

  /**
   * Tears down the physics system.
   */
  virtual void destroy() = 0;

  // TODO: physics specific methods
};