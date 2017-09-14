#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include "ShipTile.h"

class Ship
{
  public:
    typedef struct
    {
      std::string type;
      char size;
    } shipInfo;

    typedef std::vector<ShipTile>::iterator ship_it;

    Ship(const shipInfo&, char shipBeginColumn, char shipBeginRow, char shipEndColumn, char shipEndRow);

    std::string type() const;

    char size() const;

    ship_it shipBegin() ;
    ship_it shipEnd() ;

    bool isCollision(Ship&);
    bool isSunk();
    bool checkHit(char, char);
    bool checkLocation(char, char);
    bool static checkSize(char, char, char, char, char);

  private:
    shipInfo info_;
    std::vector<ShipTile> sections_;
};

#endif // SHIP_H
