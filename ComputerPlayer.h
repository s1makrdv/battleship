#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <string>
#include <list>
#include "Player.h"
#include "coord.h"
#include "Strategy.h"
#include "ConsoleDisplay.h"

class ComputerPlayer : public Player
{
  public:
    ComputerPlayer(std::string name = "Computer");

    void move(char *c, char *r, Board& board);
    void update(char c, char r);

  private:
    std::list<coord_t> coords_;
    Strategy strategy_;
};

#endif // COMPUTERPLAYER_H
