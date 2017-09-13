#include "Game.h"


Game::Game() :
  isFinished_(false)
{

}

bool Game::isGameOver() const
{
  return isFinished_;
}

void Game::gameEnd()
{
  isFinished_ = true;
}
