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

