#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <list>
#include "coord.h"
#include "Board.h"
#include "ShipTile.h"

using namespace std;

string const shipGridTop =     "        Ship Grid      ";
string const attackGridTop = "       Attack Grid     ";
string const boardTop =     "  |A|B|C|D|E|F|G|H|I|J|";
string const rowStart[Board::boardSize] = {
				" 1|",
				" 2|",
				" 3|",
				" 4|",
				" 5|",
				" 6|",
				" 7|",
				" 8|",
				" 9|",
				"10|" };

string const shipNoHit = "O";
string const shipHit = "@";
string const boardNoHit = " ";
string const boardHit = "X";

string const legend =	"---Legend---   \nO Ship         \n@ Ship with hit\nX Missed Attack\n";

Board::Board(istream& i, ostream& o) :
			in_(i), out_(o)
{
  // Initialize shipGrid
  for (int row = 1; row < 1 + boardSize; ++row) {
    for(int col = 'A'; col < 'A' + boardSize; ++col) {
      shipGrid_.push_back(BoardTile(col, row));
    }
  }
  // Initialize attackGrid
  for (int row = 1; row < 1 + boardSize; ++row) {
    for(int col = 'A'; col < 'A' + boardSize; ++col) {
      attackGrid_.push_back(BoardTile(col, row));
    }
  }
}

string displayTile(BoardTile& tile)
{
  int sel = ((int)tile.getHit() << 1) | (int)tile.getShip(); // 0 - 3
  switch(sel) {
    case 0:
      return boardNoHit + "|";
      break;

    case 1:
      return shipNoHit + "|";
      break;

    case 2:
      return boardHit + "|";
      break;

    case 3:
      return shipHit + "|";
      break;

    default:
      return "";
  }

  return "";//TEMPORARY FIX
}

void Board::writeShipGrid(ConsoleDisplay& display)
{
  vector<BoardTile>::iterator b_it;
  int row = 0;
  display.write(0, row++, shipGridTop);
  display.write(0, row++, boardTop);

  int i = 0;
  for (b_it = shipGrid_.begin(); b_it != shipGrid_.end(); ++b_it) {
    if ((*b_it).getCol() == 'A') {
      display.write(0, row, rowStart[i++]);
      display.write(0, row, displayTile(*b_it));
    }
    else if ((*b_it).getCol() == 'J') {
      display.write(0, row, displayTile(*b_it));
      ++row;
    }
    else {
      display.write(0, row, displayTile(*b_it));
    }
  }

  display.write(legend);
}

void Board::writeAttackGrid(ConsoleDisplay& display)
{
  vector<BoardTile>::iterator a_it;
  int row = 0;
  display.write(1, row++, attackGridTop);
  display.write(1, row++, boardTop);

  int i = 0;
  for (a_it = attackGrid_.begin(); a_it != attackGrid_.end(); ++a_it) {
    if ((*a_it).getCol() == 'A') {
      display.write(1, row, rowStart[i++]);
      display.write(1, row, displayTile(*a_it));
    }
    else if ((*a_it).getCol() == 'J') {
      display.write(1, row, displayTile(*a_it));
      ++row;
    }
    else {
      display.write(1, row, displayTile(*a_it));
    }
  }
}

bool readUserShipInput(istream& in
                       , char *col1
                       , char *row1
                       , char *col2
                       , char *row2)
{
  char c;
  string str;

  while(in.get(c) && isdigit(c)) {
    str.push_back(c);
  }

  *row1 = atoi(str.c_str());

  str.clear();

  if (isalpha(c)) {
    *col1 = toupper(c);
  }
  else {
    return false;
  }

  in.get(c); // consume space

  if (c != ' ')
    return false;

  while(in.get(c) && isdigit(c)){
    str.push_back(c);
  }

  *row2 = atoi(str.c_str());

  str.clear();

  if (isalpha(c)) {
    *col2 = toupper(c);
  }
  else {
    return false;
  }

  return true;
}

bool offBoard(char c1, char r1, char c2, char r2)
{
  if(r1 < 1 || r1 > 10 || r2 < 1 || r2 > 10 ||
     c1 < 'A' || c1 > 'J' || c2 < 'A' || c2 > 'J'){
    return true;
  }
  else {
    return false;
  }
}

bool Board::shipCollision_(Ship& ship)
{
  vector<Ship>::iterator vs_it;

  for (vs_it = ships_.begin(); vs_it != ships_.end(); ++vs_it) {
    if ((*vs_it).collision(ship)) {
      return true;
    }
  }
  return false;
}

void Board::markBoard_(Ship& ship)
{
vector<ShipTile>::iterator s_it;

  for (s_it = ship.shipBegin(); s_it != ship.shipEnd(); ++s_it) {
    int i = ((*s_it).getRow() - 1) * boardSize;
    i = i + (*s_it).getCol() - 'A';
    shipGrid_[i].setShip();
  }
}

void Board::shipPlacementRandom_(const Ship::shipInfo& info)
{
  static std::list<coord_t> coords;
  static bool initialized = false;
  std::list<coord_t>::iterator c_it;

  if (!initialized) {
    // Initialize a list of the shipGrid coordinates
    for (int r = 1; r < 1 + Board::boardSize; ++r) {
      for (int c = 'A'; c < 'A' + Board::boardSize; ++c) {
        coords.push_back(coord_t(c, r));
      }
    }

    initialized = true;
    // Seed rand
    srand(time(0));
  }

  bool success = false;
  while (!success) {
    // Select random coordinate
    int count = (rand() % coords.size());
    c_it = coords.begin();

    while (count--) {
      c_it++;
    }

    char c1 = (*c_it).col;
    char r1 = (*c_it).row;

    char dirSeed = rand() % 4;
    int i = 0;

    do {
      char c2, r2;
      char direction = (dirSeed + i) % 4;

      switch (direction) {
        case 0:
          c2 = c1;
          r2 = (r1 - info.size) + 1;
          break;

        case 1:
          c2 = c1;
          r2 = (r1 + info.size) - 1;
          break;

        case 2:
          c2 = (c1 - info.size) + 1;
          r2 = r1;
          break;

        case 3:
          c2 = (c1 + info.size) - 1;
          r2 = r1;
          break;

        default:
          while(1);
      }

      if (offBoard(c1, r1, c2, r2)) {
        continue;
      }

      if (!Ship::checkSize(info.size, c1, r1, c2, r2)) {
        continue;
      }

      Ship s(info, c1, r1, c2, r2);

      if (shipCollision_(s)) {
        continue;
      }
      else {
        ships_.push_back(s);
        markBoard_(s);
        coords.erase(c_it); // Delete coordinate
        success = true;
      }

    } while (!success && ++i < 4);
  }
}

void Board::placeShips()
{
  vector<Ship::shipInfo>::const_iterator s_it;

  for (s_it = shipTypes.begin(); s_it != shipTypes.end(); ++s_it)
    shipPlacementRandom_(*s_it);
}

bool Board::makeAttempt(char c, char r)
{
  int i = ((r - 1) * boardSize) + c - 'A';

  if (attackGrid_[i].getHit()) {
    return false;
  }
  else {
    attackGrid_[i].setHit();
    return true;
  }
}

bool Board::checkShot(char c, char r, string& str)
{
  vector<Ship>::iterator s_it;

  str.clear(); // clear return string

  for (s_it = ships_.begin(); s_it != ships_.end(); ++s_it) {
    if ((*s_it).checkHit(c, r)) {
      str = (*s_it).type(); // Return ship type string
      int i = ((r - 1) * boardSize) + c - 'A';
      shipGrid_[i].setHit();
      return true;
    }
  }
  return false;
}

void Board::markHit(char c, char r)
{
  int i = ((r - 1) * boardSize) + c - 'A';
  attackGrid_[i].setShip(); // Marks a ship in this tile
}

bool Board::fleetSunk() {
  vector<Ship>::iterator s_it;
  for (s_it = ships_.begin(); s_it != ships_.end(); ++s_it) {
    if (!(*s_it).sunk()) {
      return false;
    }
  }
  return true;
}
