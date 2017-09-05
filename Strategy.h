#ifndef STRATEGY_H
#define STRATEGY_H

#include "coord.h"

class Strategy
{
  public:
    typedef enum {NOCHANCE, NOTLIKELY, MAYBE, LIKELY} chance_t;
    typedef enum {NONE, UP, DOWN, LEFT, RIGHT} dir_t;

    // Constructor
    Strategy() :  up_(MAYBE),
                  down_(MAYBE),
                  left_(MAYBE),
                  right_(MAYBE),
                  last_dir_(NONE) { }

    bool valid();
    void update(char c, char r);
    bool getMove(char *c, char *r);

  private:
    void reset_();
    void set_(char c, char r);

    chance_t up_, down_, left_, right_;
    dir_t last_dir_;
    bool successful_;
    coord_t firstTry_;
    coord_t lastTry_;
};

#endif // STRATEGY_H
