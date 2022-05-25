#pragma once

#include "Object.h"

class Checkpoint : public Object {
private:
	sf::Image setImage(sf::String path) {
		sf::Image image;
		image.loadFromFile(path);

		return image;
	}

	enum State { off, on };
	State state = off;

protected:
	Checkpoint(sf::String path, int x, int y) : Object(setImage(path), 64, 64) {
		xPos = x;
		yPos = y;

		sprite.setOrigin(0, 0);
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		sprite.setPosition(xPos, yPos);
	}

public:

	virtual void update(float time) { }

	virtual sf::String toString() {
		return "Checkpoint";
	}

};