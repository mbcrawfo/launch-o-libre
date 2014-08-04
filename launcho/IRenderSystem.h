#pragma once

class IRenderSystem
{
public:
  virtual ~IRenderSystem() = default;

  /**
   * Initializes the rendering system. Should use exceptions to signal failure.
   */
  virtual void initialize() = 0;

  /**
   * Updates the rendering system.
   * @param deltaMs[in] The time elapsed since the last frame.
   */
  virtual void update(const float deltaMs) = 0;

  /**
   * Tears down the rendering system.
   */
  virtual void destroy() = 0;

  // TODO: rendering specific methods...
};