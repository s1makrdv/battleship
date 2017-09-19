#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include "Board.h"
#include "ShipTile.h"

using namespace std;

Board::Board(istream& in, ostream& out) :
                        in_(in),
                        out_(out)
{
  for (int row = 1; row < 1 + boardSize; ++row) {
    for(int col = firstColChar; col < firstColChar + boardSize; ++col) {
      shipGrid_.push_back(BoardTile(col, row));
    }
  }
  for (int row = 1; row < 1 + boardSize; ++row) {
    for(int col = firstColChar; col < firstColChar + boardSize; ++col) {
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
  vector<BoardTile>::iterator boardTileIt;
  int row = 0;
  display.write(0, row++, shipGridTop);
  display.write(0, row++, boardTop);

  int i = 0;
  for (boardTileIt = shipGrid_.begin(); boardTileIt != shipGrid_.end(); ++boardTileIt) {
    if ((*boardTileIt).getCol() == firstColChar) {
      display.write(0, row, rowStart[i++]);
      display.write(0, row, displayTile(*boardTileIt));
    }
    else if ((*boardTileIt).getCol() == lastColChar) {
      display.write(0, row, displayTile(*boardTileIt));
      ++row;
    }
    else {
      display.write(0, row, displayTile(*boardTileIt));
    }
  }

  display.write(legend);
}

void Board::writeAttackGrid(ConsoleDisplay& display)
{
  vector<BoardTile>::iterator boardTileIt;
  int row = 0;
  display.write(1, row++, attackGridTop);
  display.write(1, row++, boardTop);

  int i = 0;
  for (boardTileIt = attackGrid_.begin(); boardTileIt != attackGrid_.end(); ++boardTileIt) {
    if ((*boardTileIt).getCol() == firstColChar) {
      display.write(1, row, rowStart[i++]);
      display.write(1, row, displayTile(*boardTileIt));
    }
    else if ((*boardTileIt).getCol() == lastColChar) {
      display.write(1, row, displayTile(*boardTileIt));
      ++row;
    }
    else {
      display.write(1, row, displayTile(*boardTileIt));
    }
  }
}

bool readUserShipInput(istream& in
                       , char *shipBeginColumn
                       , char *shipBeginRow
                       , char *shipEndColumn
                       , char *shipEndRow)
{
  char c;
  string str;

  while(in.get(c) && isdigit(c)) {
    str.push_back(c);
  }

  *shipBeginRow = atoi(str.c_str());

  str.clear();

  if (isalpha(c)) {
    *shipBeginColumn = toupper(c);
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

  *shipEndRow = atoi(str.c_str());

  str.clear();

  if (isalpha(c)) {
    *shipEndColumn = toupper(c);
  }
  else {
    return false;
  }

  return true;
}

bool isOffBoard(char shipBeginColumn,
                char shipBeginRow,
                char shipEndColumn,
                char shipEndRow)
{
  if(shipBeginRow < 1 || shipBeginRow > boardSize || shipEndRow < 1 ||
     shipEndRow > boardSize || shipBeginColumn < firstColChar ||
     shipBeginColumn > lastColChar || shipEndColumn < firstColChar ||
     shipEndColumn > lastColChar){

    return true;
  }
  else {
    return false;
  }
}

bool Board::isShipCollision_(Ship& ship)
{
  vector<Ship>::iterator shipIt;

  for (shipIt = ships_.begin(); shipIt != ships_.end(); ++shipIt) {
    if ((*shipIt).isCollision(ship)) {
      return true;
    }
  }
  return false;
}

void Board::markBoard_(Ship& ship)
{
vector<ShipTile>::iterator shipTileIt;

  for (shipTileIt = ship.shipBegin(); shipTileIt != ship.shipEnd(); ++shipTileIt) {
    int i = ((*shipTileIt).getRow() - 1) * boardSize;
    i = i + (*shipTileIt).getCol() - firstColChar;
    shipGrid_[i].setShip();
  }
}

bool Board::isPlacedShipsRandom_(std::list<Coord>::iterator coordIt,
                                 const ShipInfo& info,
                                 std::list<Coord> coords)
{
  char shipBeginColumn = (*coordIt).col;
  char shipBeginRow = (*coordIt).row;

  char dirSeed = rand() % 4;
  int i = 0;

  bool isSuccess = false;

  do {
    char shipEndColumn, shipEndRow;
    char direction = (dirSeed + i) % 4;

    switch (direction) {
      case 0:
        shipEndColumn = shipBeginColumn;
        shipEndRow = (shipBeginRow - info.size) + 1;
        break;

      case 1:
        shipEndColumn = shipBeginColumn;
        shipEndRow = (shipBeginRow + info.size) - 1;
        break;

      case 2:
        shipEndColumn = (shipBeginColumn - info.size) + 1;
        shipEndRow = shipBeginRow;
        break;

      case 3:
        shipEndColumn = (shipBeginColumn + info.size) - 1;
        shipEndRow = shipBeginRow;
        break;

      default:
        while(1);
    }

    if (isOffBoard(shipBeginColumn, shipBeginRow, shipEndColumn, shipEndRow)) {
      continue;
    }

    if (!Ship::checkSize(info.size,
                         shipBeginColumn,
                         shipBeginRow,
                         shipEndColumn,
                         shipEndRow)) {
      continue;
    }

    Ship ship(info, shipBeginColumn, shipBeginRow, shipEndColumn, shipEndRow);

    if (isShipCollision_(ship)) {
      continue;
    }
    else {
      ships_.push_back(ship);
      markBoard_(ship);
      coords.erase(coordIt); // Delete coordinate
      isSuccess = true;
    }

  } while (!isSuccess && ++i < 4);

  return isSuccess;
}

void Board::shipPlacementRandom_(const ShipInfo& info)
{
  static std::list<Coord> coords;
  static bool isInitialized = false;
  std::list<Coord>::iterator coordIt;

  if (!isInitialized) {
    for (int row = 1; row < 1 + boardSize; ++row) {
      for (int col = firstColChar; col < firstColChar + boardSize; ++col) {
        coords.push_back(Coord(col, row));
      }
    }

    isInitialized = true;

    srand(time(0));
  }

  bool isSuccess = false;
  while (!isSuccess) {
    int count = (rand() % coords.size());
    coordIt = coords.begin();

    while (count--) {
      coordIt++;
    }

    isSuccess = isPlacedShipsRandom_(coordIt, info, coords);
  }
}

void Board::placeShips()
{
  vector<ShipInfo>::const_iterator shipInfoIt;

  for (shipInfoIt = shipTypes.begin(); shipInfoIt != shipTypes.end(); ++shipInfoIt)
    shipPlacementRandom_(*shipInfoIt);
}

bool Board::makeAttempt(char col, char row)
{
  int i = ((row - 1) * boardSize) + col - firstColChar;

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
  vector<Ship>::iterator shipIt;

  str.clear(); // clear return string

  for (shipIt = ships_.begin(); shipIt != ships_.end(); ++shipIt) {
    if ((*shipIt).checkHit(col, row)) {
      str = (*shipIt).type(); // Return ship type string
      int i = ((row - 1) * boardSize) + col - firstColChar;
      shipGrid_[i].setHit();
      return true;
    }
  }
  return false;
}

void Board::markHit(char col, char row)
{
  int i = ((row - 1) * boardSize) + col - firstColChar;
  attackGrid_[i].setShip(); // Marks a ship in this tile
}

bool Board::isSunkFleet()
{
  vector<Ship>::iterator shipIt;
  for (shipIt = ships_.begin(); shipIt != ships_.end(); ++shipIt) {
    if (!(*shipIt).isSunk()) {
      return false;
    }
  }
  return true;
}
