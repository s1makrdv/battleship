#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Board.h"
#include "ShipTile.h"

using namespace std;

string const shipGridTop =     "        Ship Grid      ";
string const attackGridTop = "       Attack Grid     ";
string const boardTop =     "  |A|B|C|D|E|F|G|H|I|J|";
string const rowStart[boardSize] = {
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

Board::Board(istream& in, ostream& out) :
                        in_(in),
                        out_(out)
{
  for (int row = 1; row < 1 + boardSize; ++row) {
    for(int col = 'A'; col < 'A' + boardSize; ++col) {
      shipGrid_.push_back(BoardTile(col, row));
    }
  }
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

  return "";//TODO
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

bool isOffBoard(char col1, char row1, char col2, char row2)
{
  if(row1 < 1 || row1 > boardSize || row2 < 1 || row2 > boardSize ||
     col1 < 'A' || col1 > 'J' || col2 < 'A' || col2 > 'J'){
    return true;
  }
  else {
    return false;
  }
}

bool Board::isShipCollision_(Ship& ship)
{
  vector<Ship>::iterator vs_it;

  for (vs_it = ships_.begin(); vs_it != ships_.end(); ++vs_it) {
    if ((*vs_it).isCollision(ship)) {
      return true;
    }
  }
  return false;
}

void Board::markBoard_(Ship& ship)
{
vector<ShipTile>::iterator ship_it;

  for (ship_it = ship.shipBegin(); ship_it != ship.shipEnd(); ++ship_it) {
    int i = ((*ship_it).getRow() - 1) * boardSize;
    i = i + (*ship_it).getCol() - 'A';
    shipGrid_[i].setShip();
  }
}

bool Board::isPlacedShipsRandom_(std::list<coord_t>::iterator c_it,
                             const Ship::shipInfo& info,
                             std::list<coord_t> coords)
{
  char col1 = (*c_it).col;
  char row1 = (*c_it).row;

  char dirSeed = rand() % 4;
  int i = 0;

  bool isSuccess = false;

  do {
    char col2, row2;
    char direction = (dirSeed + i) % 4;

    switch (direction) {
      case 0:
        col2 = col1;
        row2 = (row1 - info.size) + 1;
        break;

      case 1:
        col2 = col1;
        row2 = (row1 + info.size) - 1;
        break;

      case 2:
        col2 = (col1 - info.size) + 1;
        row2 = row1;
        break;

      case 3:
        col2 = (col1 + info.size) - 1;
        row2 = row1;
        break;

      default:
        while(1);
    }

    if (isOffBoard(col1, row1, col2, row2)) {
      continue;
    }

    if (!Ship::checkSize(info.size, col1, row1, col2, row2)) {
      continue;
    }

    Ship ship(info, col1, row1, col2, row2);

    if (isShipCollision_(ship)) {
      continue;
    }
    else {
      ships_.push_back(ship);
      markBoard_(ship);
      coords.erase(c_it); // Delete coordinate
      isSuccess = true;
    }

  } while (!isSuccess && ++i < 4);

  return isSuccess;
}

void Board::shipPlacementRandom_(const Ship::shipInfo& info)
{
  static std::list<coord_t> coords;
  static bool isInitialized = false;
  std::list<coord_t>::iterator c_it;

  if (!isInitialized) {
    for (int row = 1; row < 1 + boardSize; ++row) {
      for (int col = 'A'; col < 'A' + boardSize; ++col) {
        coords.push_back(coord_t(col, row));
      }
    }

    isInitialized = true;

    srand(time(0));
  }

  bool isSuccess = false;
  while (!isSuccess) {
    int count = (rand() % coords.size());
    c_it = coords.begin();

    while (count--) {
      c_it++;
    }

    isSuccess = isPlacedShipsRandom_(c_it, info, coords);
  }
}

void Board::placeShips()
{
  vector<Ship::shipInfo>::const_iterator ship_it;

  for (ship_it = shipTypes.begin(); ship_it != shipTypes.end(); ++ship_it)
    shipPlacementRandom_(*ship_it);
}

bool Board::makeAttempt(char col, char row)
{
  int i = ((row - 1) * boardSize) + col - 'A';

  if (attackGrid_[i].getHit()) {
    return false;
  }
  else {
    attackGrid_[i].setHit();
    return true;
  }
}

bool Board::checkShot(char col, char row, string& str)
{
  vector<Ship>::iterator ship_it;

  str.clear(); // clear return string

  for (ship_it = ships_.begin(); ship_it != ships_.end(); ++ship_it) {
    if ((*ship_it).checkHit(col, row)) {
      str = (*ship_it).type(); // Return ship type string
      int i = ((row - 1) * boardSize) + col - 'A';
      shipGrid_[i].setHit();
      return true;
    }
  }
  return false;
}

void Board::markHit(char col, char row)
{
  int i = ((row - 1) * boardSize) + col - 'A';
  attackGrid_[i].setShip(); // Marks a ship in this tile
}

bool Board::isSunkFleet()
{
  vector<Ship>::iterator ship_it;
  for (ship_it = ships_.begin(); ship_it != ships_.end(); ++ship_it) {
    if (!(*ship_it).isSunk()) {
      return false;
    }
  }
  return true;
}
