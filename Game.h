#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game {
public:
	// Constructor
    Game() : finished_(false), paused_(false) { }

    virtual void gameUpdate() = 0;

    bool gameOver() {
        return finished_;
	}

    void gameEnd() {
        finished_ = true;
    }

    bool getPaused() {
        return paused_;
    }

    void setPaused() {
        paused_ = true;
    }

	// Destructor
	virtual ~Game() { }

private:

    bool finished_;
    bool paused_;
};

#endif // GAME_H
