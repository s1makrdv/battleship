#ifndef COORD_H
#define COORD_H

#include "Helper.hpp"

struct Coord
{
  Coord() : col(0), row(0) { }
  Coord(char c, char r) : col(c), row(r) { }

  char col;
  char row;
};

#endif // COORD_H
