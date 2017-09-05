#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game
{
  public:
    // Constructor
    Game() : finished_(false) { }

    virtual void gameUpdate() = 0;

    // Destructor
    virtual ~Game() { }

    bool gameOver() const;
    void gameEnd();

  private:
    bool finished_;
};

inline bool Game::gameOver() const
{
    return finished_;
}

inline void Game::gameEnd()
{
    finished_ = true;
}

#endif // GAME_H



