#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Object.h"

#include "Constants.h"

class Animation {
protected:
	Object* object;
	int width;
	int heigth;

	float currentFrame = 0;
	float animationSpeed = Final::animationSpeed;

	sf::Texture deathTexture;
	int alive = 0;
	bool stop = true;


	Animation(Object* object, int width, int heigth) : object(object), width(width), heigth(heigth) {
		deathTexture.loadFromFile("images/Players/Desappearing (96x96).png");
	}

public:
	virtual void Play(sf::String state, float time) {}

	void setAnimationSpeed(float speed) {
		animationSpeed = speed;
	}
};