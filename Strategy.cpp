#include "Strategy.h"

Strategy::Strategy() :
  up_(MAYBE),
  down_(MAYBE),
  left_(MAYBE),
  right_(MAYBE),
  last_dir_(NONE)
{

}

void Strategy::update(char col, char row)
{
  if (!isValid()) {
    set_(col, row);
  }
  else {
    isSuccessful_ = true;
    if (UP == last_dir_ || DOWN == last_dir_) {
      left_ = NOTLIKELY;
      right_ = NOTLIKELY;
    }
    else {
      up_ = NOTLIKELY;
      down_ = NOTLIKELY;
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

  up_ = MAYBE;
  down_ = MAYBE;
  left_ = MAYBE;
  right_ = MAYBE;
  isSuccessful_ = true;
  last_dir_ = NONE;
}

void Strategy::set_(char col, char row)
{
  firstTry_.col = col;
  firstTry_.row = row;
  lastTry_.col = col;
  lastTry_.row = row;
}

bool Strategy::getMove(char* col, char* row)
{
  if (!isSuccessful_) {
    if (UP == last_dir_) {
      up_ = NOTLIKELY;
    }
    else if (DOWN == last_dir_) {
      down_ = NOTLIKELY;
    }
    else if (LEFT == last_dir_) {
      left_ = NOTLIKELY;
    }
    else if (RIGHT == last_dir_) {
      right_ = NOTLIKELY;
    }
  }

  bool success = false;
  while(!success) {
    if (MAYBE == up_) {
      if (UP != last_dir_) {
        last_dir_ = UP;
        lastTry_ = firstTry_;
      }

      if (1 == lastTry_.row) {
        up_ = NOCHANCE;
      }
      else {
        --lastTry_.row;
        success = true;
      }
    }
    else if (MAYBE == down_) {
      if (DOWN != last_dir_) {
        last_dir_ = DOWN;
        lastTry_ = firstTry_;
      }

      if (10 == lastTry_.row) {
        down_ = NOCHANCE;
      } else {
        ++lastTry_.row;
        success = true;
      }
    }
    else if (MAYBE == left_) {
      if (LEFT != last_dir_) {
        last_dir_ = LEFT;
        lastTry_ = firstTry_;
      }

      if ('A' == lastTry_.col) {
        left_ = NOCHANCE;
      }
      else {
        --lastTry_.col;
        success = true;
      }
    }
    else if (MAYBE == right_) {
      if (RIGHT != last_dir_) {
        last_dir_ = RIGHT;
        lastTry_ = firstTry_;
      }

      if ('J' == lastTry_.col) {
        right_ = NOCHANCE;
      }
      else {
        ++lastTry_.col;
        success = true;
      }
    }
    else {
      reset_();
      return false;
    }
  }

  *col = lastTry_.col;
  *row = lastTry_.row;
  isSuccessful_ = false;

  return true;
}
