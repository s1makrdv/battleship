#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"
#include "ConsoleDisplay.h"

class Player
{
  public:
    Player();
    Player(std::string name);

    virtual void move(char* c, char* r, Board& board) = 0;

    virtual ~Player() { }

    std::string name() const;

    void setName(const std::string& name);

  private:
    std::string name_;
};


#endif // PLAYER_H


