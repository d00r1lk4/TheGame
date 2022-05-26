#pragma once

#include "Enemy.h"

#include "Level.h"

#include "BlueBirdAnimation.h"

class BlueBird : public Enemy {
private:
	bool checkBoundsOfMap(float Dx, float Dy, Level* lvl);

	enum State { fly, hit, death };
	State state = fly;

	BlueBirdAnimation Animator{ this, 32, 32 };

public:
	BlueBird(float x, float y);

	bool update(float time, Level* lvl);

	virtual sf::String toString() {
		return "BlueBird";
	}
};