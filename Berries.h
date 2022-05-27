#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Object.h"

#include "BerriesAnimation.h"

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

	BerriesAnimation Animator{ this, 32, 32 };

	enum State {stay, collected};
	State state = stay;

public:
	virtual bool update(float time) {
		switch (state)
		{
		case stay:
			Animator.Play("stay", time);
			break;
		case collected:
			Animator.Play("collected", time);
			break;
		}

		if (isCollected && !isPlayed) {
			state = collected;

			soundBuffer.loadFromFile("sounds/eat.ogg");
			sound.setBuffer(soundBuffer);
			sound.setVolume(100);
			sound.play();

			isPlayed = true;
		}
		else if (!isCollected) {
			state = stay;
		}


		return 0;
	}

	bool checkCollected() {
		return isCollected;
	}
	void collect() {
		isCollected = true;
	}
};