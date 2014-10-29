#include "Box2DPhysics.h"
#include "utility/Log.h"
#include "utility/Timer.h"

const std::string Box2DPhysics::TAG = "Box2DPhysics";
const b2Vec2 Box2DPhysics::gravity(0.0f, -9.80665f);
const float Box2DPhysics::timeStepS = 1.0f / 60.0f;
const float Box2DPhysics::timeStepMs = timeStepS * 1000.0f;

Box2DPhysics::Box2DPhysics()
: world(),
  lastStepDeltaMs(0.0f)
{
}

std::weak_ptr<b2World> Box2DPhysics::getWorld()
{
  return world;
}

void Box2DPhysics::initialize()
{
  world = std::shared_ptr<b2World>(new b2World(gravity));
}

void Box2DPhysics::update(const float deltaMs)
{
  lastStepDeltaMs += deltaMs;
  while (lastStepDeltaMs >= timeStepMs)
  {
    lastStepDeltaMs -= timeStepMs;
    world->Step(timeStepS, 8, 3);    
  }
}

void Box2DPhysics::destroy()
{
  world = std::shared_ptr<b2World>();
}
