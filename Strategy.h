#ifndef STRATEGY_H
#define STRATEGY_H

#include "Coord.h"

enum class Chance
{
  NONE,
  NOCHANCE,
  NOTLIKELY,
  MAYBE,
  LIKELY
};

enum class Direction
{
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Strategy
{
  public:
    Strategy();

    bool isValid();
    void update(char col, char row);
    bool getMove(char* col, char* row);

  private:
    void lastDirInit_();
    void checkUpDirSuccess_();
    void checkDownDirSuccess_();
    void checkLeftDirSuccess_();
    void checkRightDirSuccess_();

    void reset_();
    void set_(char col, char row);

    Chance up_, down_, left_, right_;
    Direction    last_dir_;
    bool     isSuccess_, isCurrentDirSuccess;
    coord_t  firstTry_;
    coord_t  lastTry_;
};

#endif // STRATEGY_H
