#include "Game.h"
#include "GameOptions.h"
#include "options.h"
// do not remove include, SDL generates its own main function to handle
// windows events and needs to see our main
#include <SDL.h>

int main(int argc, char* argv[])
{
  // set some default options
  GameOptions::getInstance().setInt(SCREEN_WIDTH, 800);
  GameOptions::getInstance().setInt(SCREEN_HEIGHT, 600);
  
  //GameOptions::getInstance().parseCommandLine(argc, argv);
  //GameOptions::getInstance().loadFromFile("filename goes here");

  Game game;
  game.run();
  return 0;
}