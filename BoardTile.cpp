#include "BoardTile.h"


BoardTile::BoardTile() :
  isHit_(false),
  isShip_(false)
{

}

BoardTile::BoardTile(char c, char r) :
  Tile(c, r),
  isHit_(false),
  isShip_(false)
{

}

bool BoardTile::getHit() const
{
  return isHit_;
}

void BoardTile::setHit()
{
  isHit_ = true;
}

bool BoardTile::getShip() const
{
  return isShip_;
}

void BoardTile::setShip()
{
  isShip_ = true;
}
