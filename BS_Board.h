#ifndef BS_BOARD_H
#define BS_BOARD_H

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include "BS_BoardTile.h"
#include "Ship.h"
#include "ConsoleDisplay.h"

class BS_Board {
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

	// Constructors
	BS_Board(std::istream& i, std::ostream& o);

	void placeShips();
	bool makeAttempt(char c, char r);
	bool checkShot(char c, char r, std::string& str);
	void markHit(char c, char r);
	bool fleetSunk();
	void writeShipGrid(ConsoleDisplay& display);
	void writeAttackGrid(ConsoleDisplay& display);
private:
	bool shipCollision(Ship&);
	void shipPlacementPrompt(const Ship::shipInfo&, ConsoleDisplay& display);
	void shipPlacementRandom(const Ship::shipInfo&);
	void markBoard(Ship&);
	std::istream& in;
	std::ostream& out;
	std::vector<Ship> ships;
	std::vector<BS_BoardTile> shipGrid;
	std::vector<BS_BoardTile> attackGrid;
};

#endif //BS_BOARD_H
