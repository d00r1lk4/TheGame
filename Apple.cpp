#include "Apple.h"

#include <iostream>

Apple::Apple(float x, float y) : Berries("Apple.png", x, y, 32, 32) {
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(xPos + sprite.getLocalBounds().width / 2, yPos + sprite.getLocalBounds().height / 2);
}

void Apple::update(float time) {
	Berries::update(time);
}