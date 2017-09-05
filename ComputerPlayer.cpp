#include <cstdlib>
#include <ctime>
#include "ComputerPlayer.h"
#include "Board.h"

using namespace std;

ComputerPlayer::ComputerPlayer(std::string name) : Player(name)
{
  // Initialize a list of the board coordinates
  for (int r = 1; r < 1 + Board::boardSize; ++r) {
    for (int c = 'A'; c < 'A' + Board::boardSize; ++c) {
      coords_.push_back(coord_t(c, r));
    }
  }
  // Seed rand
  srand(time(0));
}

void ComputerPlayer::move(char *c, char *r, Board& board)
{
  list<coord_t>::iterator c_it;

  bool success = false;

  while (!success && strategy_.valid()) { // Use apriori knowlege
    strategy_.getMove(c, r);
    for (c_it = coords_.begin(); c_it != coords_.end(); ++c_it) {
      if (*c == (*c_it).col && *r == (*c_it).row) {
        success = true;
        coords_.erase(c_it);
        break;
      }
    }
  }

  if (!success) { // Select random coordinate
    int count = (rand() % coords_.size());
    c_it = coords_.begin();

    while (count--) {
      c_it++;
    }

    *c = (*c_it).col;
    *r = (*c_it).row;
    coords_.erase(c_it);
  }
}

void ComputerPlayer::update(char c, char r)
{
  strategy_.update(c, r);
}
