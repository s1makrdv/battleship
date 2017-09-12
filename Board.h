#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include "BoardTile.h"
#include "Ship.h"
#include "ConsoleDisplay.h"

class Board
{
  public:
    static int const boardSize = 10;

    const std::vector<Ship::shipInfo> shipTypes = {{ "Four-deck", 4},
                              { "Three-deck", 3},
                              { "Three-deck", 3},
                              { "Double-deck", 2},
                              { "Double-deck", 2},
                              { "Double-deck", 2},
                              { "Single-deck", 1},
                              { "Single-deck", 1},
                              { "Single-deck", 1},
                              { "Single-deck", 1}};

    Board(std::istream& i, std::ostream& o);

    void placeShips();
    bool makeAttempt(char c, char r);
    bool checkShot(char c, char r, std::string& str);
    void markHit(char c, char r);
    bool fleetSunk();
    void writeShipGrid(ConsoleDisplay& display);
    void writeAttackGrid(ConsoleDisplay& display);

  private:
    bool isShipCollision_(Ship&);
    void shipPlacementPrompt_(const Ship::shipInfo&, ConsoleDisplay& display);
    void shipPlacementRandom_(const Ship::shipInfo&);
    void markBoard_(Ship&);
    std::istream& in_;
    std::ostream& out_;
    std::vector<Ship> ships_;
    std::vector<BoardTile> shipGrid_;
    std::vector<BoardTile> attackGrid_;
};

#endif //BOARD_H
