#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"

class Player
{
  public:
    Player();
    Player(std::string name);

    virtual void move(char* col, char* row, Board& board) = 0;
    virtual void update(char col, char row) = 0;

    virtual ~Player() { }

    std::string name() const;
    void setName(const std::string& name);

    bool isSuccess() const;
    void setIsSuccess(bool isSuccess);

    int  stepNo() const;
    void setStepNo(int stepNo);
    void setStepNo();

  private:
    std::string name_;
    bool isSuccess_;
    int stepNo_;
};

inline std::string Player::name() const
{
  return name_;
}

inline void Player::setName(const std::string& name)
{
  name_ = name;
}

inline bool Player::isSuccess() const
{
  return isSuccess_;
}

inline void Player::setIsSuccess(bool isSuccess)
{
  isSuccess_ = isSuccess;
}

inline int Player::stepNo() const
{
  return stepNo_;
}

inline void Player::setStepNo()
{
  ++stepNo_;
}

inline void Player::setStepNo(int stepNo)
{
  stepNo_ = stepNo;
}

#endif // PLAYER_H


