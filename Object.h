#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Object {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	float xPos = 0.f, yPos = 0.f;

	bool facingRight = true;

	Object(sf::Image& image, float width, float height) {
		texture.loadFromImage(image);

		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}


public:
	sf::Sprite& getSprite() {
		return sprite;
	}


	void setPosX(float x) {
		xPos = x;
	}
	void setPosY(float y) {
		yPos = y;
	}

	float getPosX() {
		return xPos;
	}
	float getPosY() {
		return yPos;
	}

	sf::FloatRect getRect() {
		return sf::FloatRect(xPos, yPos, sprite.getGlobalBounds().width ,sprite.getGlobalBounds().height);
	}

	sf::Texture getTexture() {
		return texture;
	}

	bool getFacing() {
		return facingRight;
	}

	virtual sf::String toString() {
		return "Object";
	}
};