#pragma once

#include "Checkpoint.h"

class NextLevel : public Checkpoint {
private:
	enum State { off, turningOn, on };
	State state = on;

public:
	NextLevel(int x, int y) : Checkpoint("images/Items/Checkpoints/Checkpoint/Checkpoint.png", x, y) {
		xPos = x;
		yPos = y;
	}

	virtual void update(float time) {
		switch (state)
		{
		case off:

			break;
		case turningOn:

			break;
		case on:

			break;
		}
	}

	bool canGo() {
		return state == on;
	}

	virtual sf::String toString() {
		return "NextLevel";
	}

};