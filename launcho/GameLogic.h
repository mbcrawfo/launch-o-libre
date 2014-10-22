#pragma once

#include "ILogicSystem.h"
#include "Entity.h"
#include "math/Vector2.h"
#include "math/AABB2.h"
#include <map>
#include <string>

// TODO: for the moment the player will be entity id 1, will change
static const EntityID PLAYER_ID = 1;

class GameLogic final
  : public ILogicSystem
{
private:
  static const std::string TAG;

  std::map<EntityID, StrongEntityPtr> entities;
  EventCallbackID inputCallbackID;

public:
  void initialize() override;
  void update(const float deltaMs) override;
  void destroy() override;
  void addEntity(StrongEntityPtr entity) override;
  WeakEntityPtr getEntity(const EntityID id) const override;
  void removeEntity(const EntityID id) override;
  WeakEntityPtr getPlayer() override;

private:
  void inputCallback(StrongEventPtr evt);
};