#ifndef STRATEGY_H
#define STRATEGY_H

#include "coord.h"

typedef enum {NOCHANCE, NOTLIKELY, MAYBE, LIKELY} chance_t;
typedef enum {NONE, UP, DOWN, LEFT, RIGHT} dir_t;

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
    void set_(char c, char r);

    chance_t up_, down_, left_, right_;
    dir_t    last_dir_;
    bool     isSuccess_, isCurrentDirSuccess;
    coord_t  firstTry_;
    coord_t  lastTry_;
};

#endif // STRATEGY_H
