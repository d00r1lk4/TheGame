#pragma once

#include "Enemy.h"

#include "Level.h"

#include "AngryPigAnimation.h"

class AngryPig : public Enemy {
private:
	void checkBoundsOfMap(float Dx, float Dy, Level *lvl);

	enum State { walk, stay, angry, hit, death };
	State state = walk;

	AngryPigAnimation Animator{ this, 36, 30 };

public:
	AngryPig(float x, float y);

	void update(float time, Level *lvl);

	virtual sf::String toString() {
		return "AngryPig";
	}
};