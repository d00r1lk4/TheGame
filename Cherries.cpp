#include "Cherries.h"

#include <iostream>

Cherries::Cherries(float x, float y) : Berries("Cherries.png", x, y, 32, 32) {
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(xPos + sprite.getLocalBounds().width / 2, yPos + sprite.getLocalBounds().height / 2);
}

void Cherries::update(float time) {
	Berries::update(time);
}