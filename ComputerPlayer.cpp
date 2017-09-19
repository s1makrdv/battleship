#include <cstdlib>
#include <ctime>
#include "ComputerPlayer.h"
#include "Board.h"

using namespace std;

ComputerPlayer::ComputerPlayer(std::string name) : Player(name)
{
  for (int r = 1; r < 1 + boardSize; ++r) {
    for (int c = firstColChar; c < firstColChar + boardSize; ++c) {
      coords_.push_back(Coord(c, r));
    }
  }

  srand(time(0));
}

void ComputerPlayer::move(char *col, char *row, Board& board)
{
  list<Coord>::iterator coordIt;

  bool isSuccess = false;

  while (!isSuccess && strategy_.isValid()) {
    strategy_.getMove(col, row);
    for (coordIt = coords_.begin(); coordIt != coords_.end(); ++coordIt) {
      if (*col == (*coordIt).col && *row == (*coordIt).row) {
        isSuccess = true;
        coords_.erase(coordIt);
        break;
      }
    }
  }

  if (!isSuccess) {
    int count = (rand() % coords_.size());
    coordIt = coords_.begin();

    while (count--) {
      coordIt++;
    }

    *col = (*coordIt).col;
    *row = (*coordIt).row;
    coords_.erase(coordIt);
  }
}

void ComputerPlayer::update(char col, char row)
{
  strategy_.update(col, row);
}
