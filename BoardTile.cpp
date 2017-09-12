#include "BoardTile.h"


BoardTile::BoardTile() :
  hit_(false),
  ship_(false)
{

}

BoardTile::BoardTile(char c, char r) :
  Tile(c, r),
  hit_(false),
  ship_(false)
{

}

bool BoardTile::getHit() const
{
  return hit_;
}

void BoardTile::setHit()
{
  hit_ = true;
}

bool BoardTile::getShip() const
{
  return ship_;
}

void BoardTile::setShip()
{
  ship_ = true;
}
