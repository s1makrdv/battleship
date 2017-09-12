#include <stdexcept>
#include "Ship.h"

using namespace std;

bool Ship::checkSize(char size, char col1, char row1, char col2, char row2)
{
  if (row1 == row2) {
    if (col1 > col2) {
      if ((col1 - col2) + 1 == size) {
        return true;
      }
    }
    else {
      if ((col2 - col1) + 1 == size) {
        return true;
      }
    }
  }

  if (col1 == col2) {
    if (row1 > row2) {
      if ((row1 - row2) + 1 == size) {
        return true;
      }
    }
    else {
      if ((row2 - row1) + 1 == size) {
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

Ship::ship_it Ship::shipBegin()
{
    return sections_.begin();
}

Ship::ship_it Ship::shipEnd()
{
  return sections_.end();
}

void buildShipSections(std::vector<ShipTile>& tiles, char col1, char row1, char col2, char row2)
{
  int i;

  if (row1 == row2) {
    if (col1 < col2) {
      for (i = col1; i <= col2; ++i) {
        tiles.push_back(ShipTile(i,row1));
      }
    }
    else {
      for (i = col2; i <= col1; ++i) {
        tiles.push_back(ShipTile(i, row1));
      }
    }
  }
  else {
    if (row1 < row2) {
      for (i = row1; i <= row2; ++i) {
        tiles.push_back(ShipTile(col1, i));
      }
    }
    else {
      for (i = row2; i <= row1; ++i) {
        tiles.push_back(ShipTile(col1, i));
      }
    }
  }
}

Ship::Ship(const shipInfo& i, char c1, char r1, char c2, char r2)
{
  info_ = i;
  buildShipSections(sections_, c1, r1, c2, r2);
}

bool Ship::checkHit(char col, char row)
{
  for (ship_it it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getCol() == col && (*it).getRow() == row) {
      (*it).setHit();
      // FIXME: When should we check sunk cond?
      return true;
    }
  }
  return false;
}

bool Ship::sunk()
{
  for(ship_it it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getHit() == false)
      return false;
  }
  return true;
}

bool Ship::checkLocation(char col, char row)
{
  for (ship_it it = sections_.begin(); it != sections_.end(); ++it) {
    if ((*it).getCol() == col && (*it).getRow() == row)
      return true;
  }

  return false;
}

bool Ship::collision(Ship& s)
{
  bool ret = false;
  for (ship_it it1 = s.sections_.begin(); it1 != s.sections_.end(); ++it1) {
    for (ship_it it2 = sections_.begin(); it2 != sections_.end(); ++it2) {
      auto x = (*it1).getCol();
      auto y = (*it1).getRow();
      auto i = (*it2).getCol();
      auto j = (*it2).getRow();

      if( (x == i) && (y == j)) {
          ret = true;
      }

      else if(  (x == i + 1) && (y == j + 1)) {
        ret = true;
      }
      else if(  (x == i)     && (y == j + 1)) {
        ret = true;
      }
      else if(  (x == i - 1) && (y == j + 1)) {
        ret = true;
      }
      else if(  (x == i - 1) && (y == j)) {
        ret = true;
      }
      else if(  (x == i - 1) && (y == j - 1)) {
        ret = true;
      }
      else if(  (x == i)     && (y == j - 1)) {
        ret = true;
      }
      else if(  (x == i + 1) && (y == j - 1)) {
        ret = true;
      }
      else if(  (x == i + 1) && (y == j)) {
        ret = true;
      }
      else{
        ;
      }
    }
  }
  return ret;
}
