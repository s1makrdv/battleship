#include "Game.h"


Game::Game() : finished_(false) { }

bool Game::isGameOver() const
{
  return finished_;
}

void Game::gameEnd()
{
  finished_ = true;
}
