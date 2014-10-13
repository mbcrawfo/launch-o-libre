#pragma once

#include "ILogicSystem.h"

class GameLogic final
  : public ILogicSystem
{
public:
  virtual void initialize() override;
  virtual void update(const float deltaMs) override;
  virtual void destroy() override;
};