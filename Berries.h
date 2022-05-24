#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"

class Berries : public Object {
private:
	sf::Image setImage(sf::String path) {
		sf::Image image;
		image.loadFromFile("images/Items/Fruits/" + path);

		return image;
	}

protected:
	Berries(sf::String path, float x, float y, int width, int height) : Object(setImage(path), width, height) {
		xPos = x;
		yPos = y;

		sprite.setPosition(x, y);
	}

	bool isCollected = false;

public:
	virtual void update(float time) {
		//add anim

		sprite.setPosition(xPos, yPos);
	}

	bool chackCollected() {
		return isCollected;
	}
	void collected() {
		isCollected = true;
	}
};