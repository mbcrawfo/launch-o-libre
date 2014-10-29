#pragma once

#include <Box2D.h>
#include <memory>
#include <string>

class Box2DPhysics
{
private: 
  static const std::string TAG;
  static const b2Vec2 gravity;
  static const float timeStepS;
  static const float timeStepMs;
  
  std::shared_ptr<b2World> world;
  float lastStepDeltaMs;

public:
  Box2DPhysics();

  void initialize();
  void update(const float deltaMs);
  void destroy();

  std::weak_ptr<b2World> getWorld();
};