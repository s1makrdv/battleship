#ifndef DEFINE_H
#define DEFINE_H

#include "ShipTile.h"

enum class Chance
{
  NONE,
  NOCHANCE,
  NOTLIKELY,
  MAYBE,
  LIKELY
};

enum class Direction
{
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef std::vector<ShipTile>::iterator ShipIt;

typedef std::vector<std::vector<std::string> >::iterator ScreenIt;
typedef std::vector<std::string>::iterator PanelIt;

typedef struct
{
  std::string type;
  char size;
} ShipInfo;

#endif // DEFINE_H
