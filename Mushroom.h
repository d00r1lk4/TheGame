#pragma once

#include "Enemy.h"

#include "Level.h"

#include "MushroomAnimation.h"

class Mushroom : public Enemy {
private:
	bool checkBoundsOfMap(float Dx, float Dy, Level* lvl);

	enum State { walk, stay, hit, death };
	State state = walk;

	MushroomAnimation Animator{ this, 32, 32 };

public:
	Mushroom(float x, float y);

	bool update(float time, Level* lvl);

	virtual sf::String toString() {
		return "Mushroom";
	}
};