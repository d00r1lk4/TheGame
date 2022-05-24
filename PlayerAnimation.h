#pragma once

#include "Animation.h"

class PlayerAnimation : public Animation {
private:
	void PlayWalk() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
				heigth, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width,
				heigth, -width, heigth));
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
	void PlayJump() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(0, 96, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(32, 96, -width, heigth));
		}
	}
	void PlayFall() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(32, 96, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(64, 96, -width, heigth));
		}
	}

	void PlayDoubleJump() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame), 128, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width, 128, -width, heigth));
		}
	}
	void PlayWallJump() {
		if (object->getFacing()) {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame), 160, width, heigth));
		}
		else {
			object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame) + width, 160, -width, heigth));
		}
	}

	void PlayDeath() {
		object->getSprite().setTexture(deathTexture);
		object->getSprite().setOrigin(64 + 16, 64 + 16);

		object->getSprite().setTextureRect(sf::IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));

		if (currentFrame > 7) {
			stop = false;
		}
	}

public:
	PlayerAnimation(Object* object, int width, int heigth) : Animation(object, width, heigth) {}

	virtual void Play(sf::String state, float time) {
		static int frameCount = 0;

		currentFrame += animationSpeed * time;
		if (currentFrame > frameCount && stop) { currentFrame = 0; }

		if (state == "walk") {
			frameCount = 12;
			PlayWalk();
		}
		if (state == "jump") {
			PlayJump();
		}
		if (state == "fall") {
			PlayFall();
		}
		if (state == "doubleJump") {
			frameCount = 6;
			PlayDoubleJump();
		}
		if (state == "wallJump") {
			frameCount = 5;
			PlayWallJump();
		}
		if (state == "stay") {
			frameCount = 11;
			PlayIdle();
		}
		if (state == "death") {
			frameCount = 10;
			if (!alive) { currentFrame = 0; ++alive; }
			PlayDeath();
		}
	}
};