#pragma once

#include "ILogicSystem.h"
#include "Entity.h"
#include "math/Vector2.h"
#include "math/AABB2.h"
#include <map>

// TODO: This is a hacky solution until entities are more fleshed out
enum class EntityType
{
  Player,  // blue box
  Enemy,   // red box
  Terrain  // green box
};

class GameLogic final
  : public ILogicSystem
{
private:
  std::map<EntityID, StrongEntityPtr> entities;

public:
  virtual void initialize() override;
  virtual void update(const float deltaMs) override;
  virtual void destroy() override;

  /**
   * Create a basic entity that is nothing but a solid color box.
   * @param type See enum above.
   * @param pos Starting position.
   * @param size Entity size.
   */
  WeakEntityPtr createSimpleEntity(const EntityType type, const Vector2& pos,
                                   const AABB2& size);

  /**
   * Get an entity.
   * @param id Entity to retrieve.
   * @return The entity.
   */
  WeakEntityPtr getEntity(const EntityID id) const;

  /**
   * Removes an entity from the game.
   * @param id Entity to remove.
   */
  void removeEntity(const EntityID id);
};