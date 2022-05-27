#include <iostream>

#include "AngryPig.h"

AngryPig::AngryPig(float x, float y) : Enemy("AngryPig/AngryPig.png", x, y, 36, 30) {
	sprite.setTextureRect(sf::IntRect(0, 0, 36, 30));

	health = 2;
	speed = 0.025f;
	dx = speed;
}

bool AngryPig::checkBoundsOfMap(float Dx, float Dy, Level *lvl) {
	for (int i = yPos / Final::tilesRezolution; i < (yPos + sprite.getGlobalBounds().height) / Final::tilesRezolution; ++i)
	for (int j = xPos / Final::tilesRezolution; j < (xPos + sprite.getGlobalBounds().width) / Final::tilesRezolution; ++j) {
		if (lvl->getTileMap()[i][j] == '!' || lvl->getTileMap()[i][j] == 'e' || lvl->getTileMap()[i][j] == '#' ||
			lvl->getTileMap()[i][j] == '$' || lvl->getTileMap()[i][j] == '%' || lvl->getTileMap()[i][j] == '&' ||
			lvl->getTileMap()[i][j] == 'f' || lvl->getTileMap()[i][j] == '(' || lvl->getTileMap()[i][j] == ')' ||

			lvl->getTileMap()[i][j] == '9' || lvl->getTileMap()[i][j] == ':' ||
			lvl->getTileMap()[i][j] == ';' || lvl->getTileMap()[i][j] == '<' ||
			//

			//
			lvl->getTileMap()[i][j] == '0' || lvl->getTileMap()[i][j] == '1' || lvl->getTileMap()[i][j] == '2' ||
			lvl->getTileMap()[i][j] == '3' || lvl->getTileMap()[i][j] == '4' || lvl->getTileMap()[i][j] == '5' ||
			lvl->getTileMap()[i][j] == '6' || lvl->getTileMap()[i][j] == '7' || lvl->getTileMap()[i][j] == '8' ||

			lvl->getTileMap()[i][j] == '*' || lvl->getTileMap()[i][j] == '+' ||
			lvl->getTileMap()[i][j] == ',' || lvl->getTileMap()[i][j] == '-' ||
			//

			//
			lvl->getTileMap()[i][j] == '.' || lvl->getTileMap()[i][j] == '/' || lvl->getTileMap()[i][j] == '=' ||
			lvl->getTileMap()[i][j] == '>' || lvl->getTileMap()[i][j] == '?' || lvl->getTileMap()[i][j] == '@' ||
			lvl->getTileMap()[i][j] == 'A' || lvl->getTileMap()[i][j] == 'B' || lvl->getTileMap()[i][j] == 'C' ||

			lvl->getTileMap()[i][j] == 'D' || lvl->getTileMap()[i][j] == 'E' ||
			lvl->getTileMap()[i][j] == 'V' || lvl->getTileMap()[i][j] == 'G' ||
			//

			//
			lvl->getTileMap()[i][j] == 'H' || lvl->getTileMap()[i][j] == 'I' || lvl->getTileMap()[i][j] == 'J' ||
			lvl->getTileMap()[i][j] == 'K' || lvl->getTileMap()[i][j] == 'L' || lvl->getTileMap()[i][j] == 'M' ||
			lvl->getTileMap()[i][j] == 'N' || lvl->getTileMap()[i][j] == 'O' || lvl->getTileMap()[i][j] == 'Q' ||

			lvl->getTileMap()[i][j] == 'R' || lvl->getTileMap()[i][j] == 'S' ||
			lvl->getTileMap()[i][j] == 'T' || lvl->getTileMap()[i][j] == 'U' ||
			//

			//
			lvl->getTileMap()[i][j] == 'g' || lvl->getTileMap()[i][j] == 'h' || lvl->getTileMap()[i][j] == 'i' ||

			lvl->getTileMap()[i][j] == 'j' ||

			lvl->getTileMap()[i][j] == 'k' || lvl->getTileMap()[i][j] == 'l' || lvl->getTileMap()[i][j] == 'n' ||
			lvl->getTileMap()[i][j] == 'o' ||

			lvl->getTileMap()[i][j] == 'q' || lvl->getTileMap()[i][j] == 'r' || lvl->getTileMap()[i][j] == 't' ||
			//

			//
			lvl->getTileMap()[i][j] == 'u' || lvl->getTileMap()[i][j] == 'v' || lvl->getTileMap()[i][j] == 'w' ||

			lvl->getTileMap()[i][j] == 'x' ||

			lvl->getTileMap()[i][j] == 'y' || lvl->getTileMap()[i][j] == 'z' || lvl->getTileMap()[i][j] == '{' ||
			lvl->getTileMap()[i][j] == '|' ||

			lvl->getTileMap()[i][j] == '}' || lvl->getTileMap()[i][j] == '~' || lvl->getTileMap()[i][j] == 'X'
			//
			) {

			if (Dy > 0.f) { setPosY(i * Final::tilesRezolution - sprite.getGlobalBounds().height); dy = 0; }
			if (Dy < 0.f) { setPosY((i - 1) * Final::tilesRezolution + sprite.getGlobalBounds().height); dy = 0; }

			if (Dx > 0) { setPosX(j * Final::tilesRezolution - sprite.getGlobalBounds().width); facingRight = true; }
			if (Dx < 0) { setPosX((j - 1) * Final::tilesRezolution + sprite.getGlobalBounds().width); facingRight = false; }
		}
	}

	return 0;
}

bool AngryPig::update(float time, Level *lvl) {
	switch (state) {
	case walk: Animator.Play("walk", time); break;
	case stay: Animator.Play("stay", time); break;
	case angry: Animator.Play("angry", time); break;
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

		if (health == 2) {
			state = walk;
			speed = 0.025f;
		}
		else if (health == 1) {
			state = angry;
			speed = 0.05f;
		}
		else if (health <= 0) { dead(); state = death; }
	}

	return 0;
}