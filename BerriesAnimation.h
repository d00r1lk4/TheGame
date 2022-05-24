#pragma once

#include "Animation.h"

class BerriesAnimation : public Animation {
private:
	void PlayStay() {
		object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
			0, width, heigth));
	}

	void PlayCollected() {
		object->getSprite().setTextureRect(sf::IntRect(width * static_cast<int>(currentFrame),
			32, width, heigth));

		if (currentFrame > 7) {
			stop = false;
		}
	}

public:
	BerriesAnimation(Object* object, int width, int heigth) : Animation(object, width, heigth) {}

	virtual void Play(sf::String state, float time) {
		static int frameCount = 0;

		currentFrame += animationSpeed * time;
		if (currentFrame > frameCount && stop) { currentFrame = 0; }

		if (state == "stay") {
			frameCount = 17;
			PlayStay();
		}
		if (state == "collected") {
			frameCount = 10;
			if (!alive) { currentFrame = 0; ++alive; }
			PlayCollected();
		}
	}
};