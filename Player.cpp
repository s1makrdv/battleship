#include "Player.h"


Player::Player()
{

}

Player::Player(std::string name) :
  name_(name)
{

}

std::string Player::name() const
{
  return name_;
}

void Player::setName(const std::string& name)
{
  name_ = name;
}

bool Player::isSuccess() const
{
  return isSuccess_;
}

void Player::setIsSuccess(bool isSuccess)
{
  isSuccess_ = isSuccess;
}

int Player::stepNo() const
{
    return stepNo_;
}

void Player::setStepNo(int stepNo)
{
    stepNo_ = stepNo;
}

void Player::setStepNo()
{
    ++stepNo_;
}

