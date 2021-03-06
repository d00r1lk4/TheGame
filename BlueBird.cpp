#include <SFML/Audio.hpp>
#include <iostream>

#include "BlueBird.h"

BlueBird::BlueBird(float x, float y) : Enemy("BlueBird/BlueBird.png", x, y, 32, 32) {
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	speed = 0.035f;
	dx = -speed;

	soundBuffer.loadFromFile("sounds/bird.ogg");
	sound.setBuffer(soundBuffer);
	sound.setVolume(30);
}

bool BlueBird::checkBoundsOfMap(float Dx, float Dy, Level* lvl) {
	for (int i = yPos / Final::tilesRezolution; i < (yPos + sprite.getGlobalBounds().height) / Final::tilesRezolution; ++i)
		for (int j = xPos / Final::tilesRezolution; j < (xPos + sprite.getGlobalBounds().width) / Final::tilesRezolution; ++j) {
			if (lvl->getTileMap()[i][j] == '0' || lvl->getTileMap()[i][j] == '1' || lvl->getTileMap()[i][j] == '2' || lvl->getTileMap()[i][j] == '3' ||
				lvl->getTileMap()[i][j] == '4' || lvl->getTileMap()[i][j] == '5' || lvl->getTileMap()[i][j] == '6' || lvl->getTileMap()[i][j] == '7' ||
				lvl->getTileMap()[i][j] == '8' || lvl->getTileMap()[i][j] == '&') {

				if (Dy > 0.f) { setPosY(i * Final::tilesRezolution - sprite.getGlobalBounds().height); }
				if (Dy < 0.f) { setPosY((i - 1) * Final::tilesRezolution + sprite.getGlobalBounds().height); }

				if (Dx > 0) { setPosX(j * Final::tilesRezolution - sprite.getGlobalBounds().width); dx = -speed; facingRight = true; sound.play(); }
				if (Dx < 0) { setPosX((j - 1) * Final::tilesRezolution + sprite.getGlobalBounds().width); dx = speed; facingRight = false; sound.play(); }
			}
		}

	return 0;
}

bool BlueBird::update(float time, Level* lvl) {
	switch (state) {
	case fly: Animator.Play("fly", time); break;
	case hit: Animator.Play("hit", time); break;
	case death: dx = 0; dy = 0;	Animator.Play("death", time); break;
	}

	if (isAlive) {
		xPos += dx * time;
		checkBoundsOfMap(dx, 0, lvl);

		sprite.setPosition(xPos + sprite.getGlobalBounds().width / 2, yPos + sprite.getGlobalBounds().height / 2);

		if (health > 0) { state = fly; }
		else if (health <= 0 && !isPlayed) {
			dead();
			state = death;

			soundBuffer.loadFromFile("sounds/kill.ogg");
			sound.setBuffer(soundBuffer);
			sound.setVolume(100);
			sound.play();

			isPlayed = true;
		}
	}

	return 0;
}