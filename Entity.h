#pragma once

#include "Object.h"

class Level;

class Entity : public Object {
protected:
	float dx, dy;
	float speed;

	float moveTimer;

	bool onGround = false;
	bool isAlive = true;

	int health;


	Entity(sf::Image &image, float x, float y, float width, float height) : Object(image, width, height) {
		xPos = x; yPos = y; moveTimer = 0;
		speed = 1; health = 1; dx = 0; dy = 0;
		isAlive = true; onGround = false;
	}

	virtual void checkBoundsOfMap(float Dx, float Dy, Level *lvl) {};


public:

	virtual void update(float time, Level *lvl) {};


	void setSpeed(float speed) {
		this->speed = speed;
	}


	float getDx() {
		return dx;
	}
	float getDy() {
		return dy;
	}
	void setDy(float Dy) {
		dy = Dy;
	}


	bool checkAlive() {
		return isAlive;
	}
	bool checkGround() {
		return onGround;
	}

	void hit() {
		--health;
	}
	virtual void dead() {
		dx = 0;
		isAlive = false;
	}

	virtual sf::String toString() {
		return "Entity";
	}
};