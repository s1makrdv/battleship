#include <cstdlib>
#include <ctime>
#include "ComputerPlayer.h"
#include "Board.h"

using namespace std;

ComputerPlayer::ComputerPlayer(std::string name) : Player(name)
{
  for (int r = 1; r < 1 + Board::boardSize; ++r) {
    for (int c = 'A'; c < 'A' + Board::boardSize; ++c) {
      coords_.push_back(coord_t(c, r));
    }
  }

  srand(time(0));
}

void ComputerPlayer::move(char *col, char *row, Board& board)
{
  list<coord_t>::iterator c_it;

  bool isSuccess = false;

  while (!isSuccess && strategy_.isValid()) {
    strategy_.getMove(col, row);
    for (c_it = coords_.begin(); c_it != coords_.end(); ++c_it) {
      if (*col == (*c_it).col && *row == (*c_it).row) {
        isSuccess = true;
        coords_.erase(c_it);
        break;
      }
    }
  }

  if (!isSuccess) {
    int count = (rand() % coords_.size());
    c_it = coords_.begin();

    while (count--) {
      c_it++;
    }

    *col = (*c_it).col;
    *row = (*c_it).row;
    coords_.erase(c_it);
  }
}

void ComputerPlayer::update(char col, char row)
{
  strategy_.update(col, row);
}
