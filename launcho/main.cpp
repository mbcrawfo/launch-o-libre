#include "Game.h"
#include "GameOptions.h"
#include "options.h"
#include "utility/Log.h"
#include <string>

static const std::string TAG = "main";

int main(int argc, char* argv[])
{
#ifdef _DEBUG
  Log::getInstance().setConsoleOutputEnable(true);
  Log::getInstance().setLevel(LogLevel::Debug);
#else
  Log::getInstance().setLevel(LogLevel::Debug);
#endif
  Log::getInstance().print(TAG, "Launch-o-Libre started");

  // set some default options
  GameOptions::getInstance().setString(WINDOW_TITLE, "Launch-o-Libre");
  GameOptions::getInstance().setInt(SCREEN_WIDTH, 800);
  GameOptions::getInstance().setInt(SCREEN_HEIGHT, 600);
  
  // TODO: Implement these
  //GameOptions::getInstance().loadFromFile("filename goes here");
  //GameOptions::getInstance().parseCommandLine(argc, argv); 
  
  GameOptions::getInstance().dumpToLog();
  Game::getInstance().run();
  return 0;
}