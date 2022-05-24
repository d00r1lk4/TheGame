#include "Strawberry.h"

#include <iostream>

Strawberry::Strawberry(float x, float y) : Berries("Strawberry.png", x, y, 32, 32) {
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(xPos + sprite.getLocalBounds().width / 2, yPos + sprite.getLocalBounds().height / 2);
}

void Strawberry::update(float time) {
	Berries::update(time);
}