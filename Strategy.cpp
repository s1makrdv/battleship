#include "Strategy.h"

Strategy::Strategy() :
  up_(Chance::MAYBE),
  down_(Chance::MAYBE),
  left_(Chance::MAYBE),
  right_(Chance::MAYBE),
  last_dir_(Direction::NONE)
{

}

void Strategy::update(char col, char row)
{
  if (!isValid()) {
    set_(col, row);
  }
  else {
    isSuccess_ = true;
    if (Direction::UP == last_dir_ || Direction::DOWN == last_dir_) {
      left_ = Chance::NOTLIKELY;
      right_ = Chance::NOTLIKELY;
    }
    else {
      up_ = Chance::NOTLIKELY;
      down_ = Chance::NOTLIKELY;
    }
  }
}

bool Strategy::isValid()
{
  if (firstTry_.col) {
    return true;
  }
  else {
    return false;
  }
}

void Strategy::reset_()
{
  firstTry_.col = 0;
  firstTry_.row = 0;
  lastTry_.col = 0;
  lastTry_.row = 0;

  up_ = Chance::MAYBE;
  down_ = Chance::MAYBE;
  left_ = Chance::MAYBE;
  right_ = Chance::MAYBE;
  isSuccess_ = true;
  last_dir_ = Direction::NONE;
}

void Strategy::set_(char col, char row)
{
  firstTry_.col = col;
  firstTry_.row = row;
  lastTry_.col = col;
  lastTry_.row = row;
}

void Strategy::lastDirInit_()
{
  if (!isSuccess_) {
    if (Direction::UP == last_dir_) {
      up_ = Chance::NOTLIKELY;
    }
    else if (Direction::DOWN == last_dir_) {
      down_ = Chance::NOTLIKELY;
    }
    else if (Direction::LEFT == last_dir_) {
      left_ = Chance::NOTLIKELY;
    }
    else if (Direction::RIGHT == last_dir_) {
      right_ = Chance::NOTLIKELY;
    }
  }
}

void Strategy::checkUpDirSuccess_()
{
  if (Direction::UP != last_dir_) {
    last_dir_ = Direction::UP;
    lastTry_ = firstTry_;
  }

  if (1 == lastTry_.row) {
    up_ = Chance::NOCHANCE;
  }
  else {
    --lastTry_.row;
    isCurrentDirSuccess = true;
  }
}

void Strategy::checkDownDirSuccess_()
{
  if (Direction::DOWN != last_dir_) {
    last_dir_ = Direction::DOWN;
    lastTry_ = firstTry_;
  }

  if (10 == lastTry_.row) {
    down_ = Chance::NOCHANCE;
  } else {
    ++lastTry_.row;
    isCurrentDirSuccess = true;
  }
}

void Strategy::checkLeftDirSuccess_()
{
  if (Direction::LEFT != last_dir_) {
    last_dir_ = Direction::LEFT;
    lastTry_ = firstTry_;
  }

  if (firstColChar == lastTry_.col) {
    left_ = Chance::NOCHANCE;
  }
  else {
    --lastTry_.col;
    isCurrentDirSuccess = true;
  }
}

void Strategy::checkRightDirSuccess_()
{
  if (Direction::RIGHT != last_dir_) {
    last_dir_ = Direction::RIGHT;
    lastTry_ = firstTry_;
  }

  if (lastColChar == lastTry_.col) {
    right_ = Chance::NOCHANCE;
  }
  else {
    ++lastTry_.col;
    isCurrentDirSuccess = true;
  }
}

bool Strategy::getMove(char* col, char* row)
{
  lastDirInit_();

  isCurrentDirSuccess = false;
  while(!isCurrentDirSuccess) {
    if (Chance::MAYBE == up_) {
      checkUpDirSuccess_();
    }
    else if (Chance::MAYBE == down_) {
      checkDownDirSuccess_();
    }
    else if (Chance::MAYBE == left_) {
      checkLeftDirSuccess_();
    }
    else if (Chance::MAYBE == right_) {
      checkRightDirSuccess_();
    }
    else {
      reset_();
      return false;
    }
  }

  *col = lastTry_.col;
  *row = lastTry_.row;
  isSuccess_ = false;

  return true;
}
