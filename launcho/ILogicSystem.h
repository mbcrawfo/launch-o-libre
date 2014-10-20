#pragma once

#include "Entity.h"
#include "types.h"

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

  // Adds an entity to the logic system.
  virtual void addEntity(StrongEntityPtr entity) = 0;

  /**
  * Get an entity.
  * @param id Entity to retrieve.
  * @return The entity.
  */
  virtual WeakEntityPtr getEntity(const EntityID id) const = 0;

  /**
  * Removes an entity from the game.
  * @param id Entity to remove.
  */
  virtual void removeEntity(const EntityID id) = 0;
};