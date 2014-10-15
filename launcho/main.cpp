#include "Game.h"
#include "GameOptions.h"
#include "options.h"
#include "utility/Log.h"

int main(int argc, char* argv[])
{
  // set some default options
  GameOptions::getInstance().setString(WINDOW_TITLE, "Launch-o-Libre");
  GameOptions::getInstance().setInt(SCREEN_WIDTH, 800);
  GameOptions::getInstance().setInt(SCREEN_HEIGHT, 600);
  
  // TODO: Implement these
  //GameOptions::getInstance().loadFromFile("filename goes here");
  //GameOptions::getInstance().parseCommandLine(argc, argv);  
  

  Game game;
  game.run();
  return 0;
}