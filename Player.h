#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"
#include "ConsoleDisplay.h"

class Player
{
  public:
    Player() { }
    Player(std::string name) : n_(name) { }

    virtual void move(char* c, char* r, Board& board) = 0;

    virtual ~Player() { }

    std::string name() const;

  protected:
    std::string n_;
};

inline std::string Player::name() const
{
    return n_;
}

#endif // PLAYER_H


