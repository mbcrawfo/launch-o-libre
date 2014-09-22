#include "SDLRenderer.h"
#include "GameOptions.h"
#include "options.h"
#include <exception>

void SDLRenderer::initialize(const std::string& windowTitle)
{
  int width = GameOptions::getInstance().getInt(SCREEN_WIDTH);
  int height = GameOptions::getInstance().getInt(SCREEN_HEIGHT);
  window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height,
                            SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    throw std::runtime_error("Unable to create window");
  }

  surface = SDL_GetWindowSurface(window);
}

void SDLRenderer::update(const float deltaMs)
{
  static SDL_Surface* rect = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
  static SDL_Rect pos = { 0, 0, 100, 100 };
  float time = 0;

  time += deltaMs;
  if (time > 2)
  {
    time = 0;
    pos.x += 10;
    pos.y += 10;
  }

  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  SDL_BlitSurface(rect, nullptr, surface, &pos);

  SDL_UpdateWindowSurface(window);
}

void SDLRenderer::destroy()
{
  SDL_DestroyWindow(window);
  surface = nullptr;
  window = nullptr;
}

