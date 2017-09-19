#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include "ShipTile.h"
#include "define.h"

class Ship
{
  public:
    Ship(const ShipInfo&, char shipBeginColumn, char shipBeginRow, char shipEndColumn, char shipEndRow);

    std::string type() const;

    char size() const;

    ShipIt shipBegin() ;
    ShipIt shipEnd() ;

    bool isCollision(Ship&);
    bool isSunk();
    bool checkHit(char, char);
    bool checkLocation(char, char);
    bool static checkSize(char, char, char, char, char);

  private:
    ShipInfo info_;
    std::vector<ShipTile> sections_;
};

#endif // SHIP_H
