#pragma once

#include "Entity.h"

#include "Level.h"

#include "PlayerAnimation.h"

class Player : public Entity {
private:
	int playerScore = 0;

	bool canJump = true;	//bhop off
	int countOfJump = Final::countOfJumps;

	int currentLevel = 0;

	enum State { walk, jump, fall, doubleJump, wallJump, stay, death };
	State state = stay;

	PlayerAnimation Animator{ this, 32, 32 };

	sf::Image setRandomSprite();

	void controller(float time);
	void checkBoundsOfMap(float Dx, float Dy, Level *lvl);

public:
	Player(float x, float y);

	void update(float time, Level *lvl);

	int getScore();
	void setScore(int score) {
		playerScore = score;
	}

	virtual sf::String toString() {
		return "Player";
	}

	int getCurrentLevel() {
		return currentLevel;
	}
	void setLevel(int level) {
		currentLevel = level;
	}

	void giveJump() {
		countOfJump = 1;
	}

	void revive() {
		isAlive = true;
	}
};