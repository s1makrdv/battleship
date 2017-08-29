#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"
#include "ConsoleDisplay.h"

class Player {
public:
    Player() { }
    Player(std::string name) : n_(name) { }

	std::string name() {
        return n_;
	}

    virtual void move(char* c, char* r, Board& board) = 0;

    virtual ~Player() { }

protected:
    std::string n_;
};

#endif // PLAYER_H
