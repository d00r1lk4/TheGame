#pragma once

#include "Object.h"

class Traps : public Object {
private:
	sf::Image setImage(sf::String path) {
		sf::Image image;
		image.loadFromFile("images/Traps/" + path);

		return image;
	}

protected:
	Traps(sf::String path, float x, float y, int width, int height) : Object(setImage(path), width, height) {
		xPos = x + 8;
		yPos = y + 8;

		sprite.setPosition(xPos, yPos);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}


public:
	virtual void update(float time) {
		sprite.setPosition(xPos, yPos);
	}


};