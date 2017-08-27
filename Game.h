#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game {
public:
	// Constructor
    Game() : finished(false), paused(false) { }

    virtual void gameUpdate() = 0;

    bool gameOver() {
		return finished;
	}

    void gameEnd() {
        finished = true;
    }

    bool getPaused() {
        return paused;
    }

    void setPaused() {
        paused = true;
    }

	// Destructor
	virtual ~Game() { }

private:

	bool finished;
    bool paused;
};

#endif // GAME_H
