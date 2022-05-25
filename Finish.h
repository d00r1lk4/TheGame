#pragma once

#include "Checkpoint.h"

class Finish : public Checkpoint {
private:
	enum State { off, on };
	State state = off;

public:
	Finish(int x, int y) : Checkpoint("images/Items/Checkpoints/End/End.png", x, y) {
		xPos = x;
		yPos = y;
	}

	virtual void update(float time) {
		switch (state)
		{
		case off:

			break;
		case on:

			break;
		default:
			break;
		}
	}

	virtual sf::String toString() {
		return "Finish";
	}

};