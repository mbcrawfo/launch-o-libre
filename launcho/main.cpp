#include "Game.h"
// do not remove include, SDL generates its own main function to handle
// windows events and needs to see our main
#include <SDL.h>

int main(int argc, char* argv[])
{
  Game game(argc, argv);
  game.run();
  return 0;
}