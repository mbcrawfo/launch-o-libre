#pragma once

#include "IRenderSystem.h"
#include <SDL.h>

class SDLRenderer final
  : public IRenderSystem
{
private:
  SDL_Window* window;
  SDL_Surface* surface;

public:
  virtual void initialize() override;
  virtual void update(const float deltaMs) override;
  virtual void destroy() override;
};