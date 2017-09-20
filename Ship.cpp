#include <stdexcept>
#include "Ship.h"

using namespace std;

bool Ship::checkSize(char size, char shipBeginColumn, char shipBeginRow, char shipEndColumn, char shipEndRow)
{
  if (shipBeginRow == shipEndRow) {
    if (shipBeginColumn > shipEndColumn) {
      if ((shipBeginColumn - shipEndColumn) + 1 == size) {
        return true;
      }
    }
    else {
      if ((shipEndColumn - shipBeginColumn) + 1 == size) {
        return true;
      }
    }
  }

  if (shipBeginColumn == shipEndColumn) {
    if (shipBeginRow > shipEndRow) {
      if ((shipBeginRow - shipEndRow) + 1 == size) {
        return true;
      }
    }
    else {
      if ((shipEndRow - shipBeginRow) + 1 == size) {
        return true;
      }
    }
  }

  return false;
}


std::string Ship::type() const
{
    return info_.type;
}

char Ship::size() const
{
    return info_.size;
}

ShipIt Ship::shipBegin()
{
    return sections_.begin();
}

ShipIt Ship::shipEnd()
{
  return sections_.end();
}

void buildShipSections(std::vector<ShipTile>& tiles, char shipBeginColumn, char shipBeginRow, char shipEndColumn, char shipEndRow)
{
  int i;

  if (shipBeginRow == shipEndRow) {
    if (shipBeginColumn < shipEndColumn) {
      for (i = shipBeginColumn; i <= shipEndColumn; ++i) {
        tiles.push_back(ShipTile(i,shipBeginRow));
      }
    }
    else {
      for (i = shipEndColumn; i <= shipBeginColumn; ++i) {
        tiles.push_back(ShipTile(i, shipBeginRow));
      }
    }
  }
  else {
    if (shipBeginRow < shipEndRow) {
      for (i = shipBeginRow; i <= shipEndRow; ++i) {
        tiles.push_back(ShipTile(shipBeginColumn, i));
      }
    }
    else {
      for (i = shipEndRow; i <= shipBeginRow; ++i) {
        tiles.push_back(ShipTile(shipBeginColumn, i));
      }
    }
  }
}

Ship::Ship(const ShipInfo& i, char shipBeginColumn, char shipBeginRow, char shipEndColumn, char shipEndRow)
{
  info_ = i;
  buildShipSections(sections_, shipBeginColumn, shipBeginRow, shipEndColumn, shipEndRow);
}

bool Ship::checkHit(char col, char row)
{
  for (ShipIt it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getCol() == col && (*it).getRow() == row) {
      (*it).setHit();
      // FIXME: When should we check sunk cond?
      return true;
    }
  }
  return false;
}

bool Ship::isSunk()
{
  for(ShipIt it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getHit() == false)
      return false;
  }
  return true;
}

bool Ship::checkLocation(char col, char row)
{
  for (ShipIt it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getCol() == col && (*it).getRow() == row)
      return true;
  }

  return false;
}

bool Ship::isCollision(Ship& ship)
{
  for (ShipIt it1 = ship.sections_.begin(); it1 != ship.sections_.end(); ++it1) {
    for (ShipIt it2 = sections_.begin(); it2 != sections_.end(); ++it2) {
      auto x = (*it1).getCol();
      auto y = (*it1).getRow();
      auto i = (*it2).getCol();
      auto j = (*it2).getRow();

      for(int k = - 1; k <= 1 ; ++k){
        for(int n = -1; n <= 1 ; ++n){
          if((x == (i + k))&&((y == (j + n)))){
            return true;
          }
        }
      }

    }
  }
  return false;
}
