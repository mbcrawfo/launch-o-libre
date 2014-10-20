#pragma once

#include "ILogicSystem.h"
#include "Entity.h"
#include "math/Vector2.h"
#include "math/AABB2.h"
#include <map>

class GameLogic final
  : public ILogicSystem
{
private:
  std::map<EntityID, StrongEntityPtr> entities;

public:
  void initialize() override;
  void update(const float deltaMs) override;
  void destroy() override;
  void addEntity(StrongEntityPtr entity) override;
  WeakEntityPtr getEntity(const EntityID id) const override;
  void removeEntity(const EntityID id) override;
};