#ifndef COORD_H
#define COORD_H

#include "Helper.hpp"
#include "define.h"

struct Coord
{
  Coord();
  Coord(char c, char r);

  char col;
  char row;
};

#endif // COORD_H
