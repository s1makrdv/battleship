#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game
{
  public:
    Game();

    virtual void gameUpdate() = 0;

    virtual ~Game() { }

    bool isGameOver() const;
    void gameEnd();

  private:
    bool finished_;
};

#endif // GAME_H



