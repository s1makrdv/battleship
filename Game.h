#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game
{
  public:
    Game() : finished_(false) { }

    virtual void gameUpdate() = 0;

    virtual ~Game() { }

    bool isGameOver() const;
    void gameEnd();

  private:
    bool finished_;
};

inline bool Game::isGameOver() const
{
    return finished_;
}

inline void Game::gameEnd()
{
    finished_ = true;
}

#endif // GAME_H



