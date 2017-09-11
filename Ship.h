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

    // Constructors
    Ship(const shipInfo&, char c1, char r1, char c2, char r2);

    std::string type() const;

    char size() const;

    std::vector<ShipTile>::iterator shipBegin() ;
    std::vector<ShipTile>::iterator shipEnd() ;

    bool collision(Ship&);
    bool sunk();
    bool checkHit(char, char);
    bool checkLocation(char, char);
    bool static checkSize(char, char, char, char, char);

  private:
    shipInfo info_;
    std::vector<ShipTile> sections_;
};

#endif // SHIP_H