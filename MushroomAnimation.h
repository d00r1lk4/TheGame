#pragma once

#include "Animation.h"

class MushroomAnimation : public Animation {
private:
	void PlayWalk() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
				32, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width,
				32, -width, heigth));
		}
	}
	void PlayIdle() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
				0, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width,
				0, -width, heigth));
		}
	}
	void PlayHit() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
				64, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width,
				64, -width, heigth));
		}
	}

	void PlayDeath() {
		object->getSprite().setTexture(deathTexture);
		object->getSprite().setOrigin(48, 48);

		object->getSprite().setTextureRect(sf::IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));

		if (currentFrame > 7) {
			stop = false;
		}
	}

public:
	MushroomAnimation(Object* object, int width, int heigth) : Animation(object, width, heigth) {}

	virtual void Play(sf::String state, float time) {
		static int frameCount = 0;

		currentFrame += animationSpeed * time;
		if (currentFrame > frameCount && stop) { currentFrame = 0; }

		if (state == "walk") {
			frameCount = 16;
			PlayWalk();
		}
		if (state == "stay") {
			frameCount = 14;
			PlayIdle();
		}
		if (state == "hit") {
			frameCount = 5;
			PlayHit();
		}
		if (state == "death") {
			frameCount = 10;
			if (!alive) { currentFrame = 0; ++alive; }
			PlayDeath();
		}
	}
};