#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <list>
#include "Coord.h"
#include "BoardTile.h"
#include "Ship.h"
#include "ConsoleDisplay.h"

class Board
{
  public:


    Board(std::istream& in, std::ostream& out);

    void placeShips();
    bool makeAttempt(char col, char row);
    bool checkShot(char col, char row, std::string& str);
    void markHit(char col, char row);
    bool isSunkFleet();
    void writeShipGrid(ConsoleDisplay& display);
    void writeAttackGrid(ConsoleDisplay& display);

  private:
    bool isShipCollision_(Ship&);
    void shipPlacementPrompt_(const ShipInfo&, ConsoleDisplay& display);
    bool isPlacedShipsRandom_(std::list<Coord>::iterator coordIt,
                           const ShipInfo& info,
                           std::list<Coord> coords);
    void shipPlacementRandom_(const ShipInfo&);
    void markBoard_(Ship&);
    std::istream& in_;
    std::ostream& out_;
    std::vector<Ship> ships_;
    std::vector<BoardTile> shipGrid_;
    std::vector<BoardTile> attackGrid_;

};

#endif //BOARD_H
