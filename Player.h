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

    bool isSuccess() const;
    void setIsSuccess(bool isSuccess);

    int stepNo() const;
    void setStepNo(int stepNo);
    void setStepNo();

  private:
    std::string name_;
    bool isSuccess_;
    int stepNo_;
};


#endif // PLAYER_H


