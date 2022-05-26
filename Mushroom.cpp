#include <iostream>

#include "Mushroom.h"

Mushroom::Mushroom(float x, float y) : Enemy("Mushroom/Mushroom.png", x, y, 32, 32) {
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	health = 1;
	speed = 0.03f;
	dx = speed;
}

bool Mushroom::checkBoundsOfMap(float Dx, float Dy, Level* lvl) {
	for (int i = yPos / Final::tilesRezolution; i < (yPos + sprite.getGlobalBounds().height) / Final::tilesRezolution; ++i)
		for (int j = xPos / Final::tilesRezolution; j < (xPos + sprite.getGlobalBounds().width) / Final::tilesRezolution; ++j) {
			if (lvl->getTileMap()[i][j] == '0' || lvl->getTileMap()[i][j] == '1' || lvl->getTileMap()[i][j] == '2' || lvl->getTileMap()[i][j] == '3' ||
				lvl->getTileMap()[i][j] == '4' || lvl->getTileMap()[i][j] == '5' || lvl->getTileMap()[i][j] == '6' || lvl->getTileMap()[i][j] == '7' || lvl->getTileMap()[i][j] == '8') {

				if (Dy > 0.f) { setPosY(i * Final::tilesRezolution - sprite.getGlobalBounds().height); dy = 0; }
				if (Dy < 0.f) { setPosY((i - 1) * Final::tilesRezolution + sprite.getGlobalBounds().height); dy = 0; }

				if (Dx > 0) { setPosX(j * Final::tilesRezolution - sprite.getGlobalBounds().width); facingRight = true; }
				if (Dx < 0) { setPosX((j - 1) * Final::tilesRezolution + sprite.getGlobalBounds().width); facingRight = false; }
			}
		}

	return 0;
}

bool Mushroom::update(float time, Level* lvl) {
	switch (state) {
	case walk: Animator.Play("walk", time); break;
	case stay: Animator.Play("stay", time); break;
	case hit: Animator.Play("hit", time); break;
	case death: dx = 0; dy = 0;	Animator.Play("death", time); break;
	}

	if (isAlive) {
		xPos += dx * time;
		checkBoundsOfMap(dx, 0, lvl);

		yPos += dy * time;
		dy += Final::gravitation * time;
		checkBoundsOfMap(0, dy, lvl);

		sprite.setPosition(xPos + sprite.getGlobalBounds().width / 2, yPos + sprite.getGlobalBounds().height / 2);

		if (facingRight) {
			dx = -speed;
		}
		else {
			dx = speed;
		}

		if (health == 1) {
			state = walk;
		}
		else if (health <= 0) { dead(); state = death; }
	}

	return 0;
}