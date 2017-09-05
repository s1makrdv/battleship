#ifndef HUMANPLAYER
#define HUMANPLAYER

#include <iostream>
#include <string>
#include "Player.h"
#include "Board.h"

class HumanPlayer : public Player
{
  public:
    HumanPlayer(std::istream& i = std::cin, std::ostream& o = std::cout);

    void move(char*, char*, Board& board);

  private:
    bool readUserShotInput_(char*, char*);

    std::istream& in_;
    std::ostream& out_;
};

#endif // HUMANPLAYER
