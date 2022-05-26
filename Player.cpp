#include <iostream>

#include "Player.h"

sf::Image Player::setRandomSprite() {
	sf::Image playerImage;

	srand((unsigned int)time(NULL));
	int randomSprite = rand() % 4;

	switch (randomSprite)
	{
	case 0: playerImage.loadFromFile("images/Players/Frog(32x32).png"); break;
	case 1: playerImage.loadFromFile("images/Players/MaskDude(32x32).png"); break;
	case 2: playerImage.loadFromFile("images/Players/PinkMan(32x32).png"); break;
	case 3: playerImage.loadFromFile("images/Players/VirtualGuy(32x32).png"); break;

	}

	return playerImage;
}

Player::Player(float x, float y) : Entity(setRandomSprite(), x, y, Final::playerRezolution, Final::playerRezolution) {
	speed = Final::playerSpeed;

	health = 3;

	sprite.setTextureRect(sf::IntRect(0, 0, Final::playerRezolution, Final::playerRezolution));
}


bool Player::update(float time, Level *lvl) {
	controller(time);

	switch (state) {
		case walk: Animator.Play("walk", time); break;
		case jump: Animator.Play("jump", time); break;
		case fall: Animator.Play("fall", time); break;
		case doubleJump: Animator.Play("doubleJump", time); break;
		case wallJump: Animator.Play("wallJump", time); break;
		case stay: Animator.Play("stay", time); break;
		case death: Animator.Play("death", time); break;
	}

	bool finish = 0;

	xPos += dx * time;
	finish = checkBoundsOfMap(dx, 0, lvl);

	dy += Final::gravitation * time;
	yPos += dy * time;
	finish = checkBoundsOfMap(0, dy, lvl);

	sprite.setPosition(xPos + sprite.getGlobalBounds().width / 2, yPos + sprite.getGlobalBounds().height / 2);

	if (health <= 0) { isAlive = false; }

	return finish;
}




void Player::controller(float time) {
	if (isAlive) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (onGround) { state = walk; }

			dx = -speed;

			facingRight = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (onGround) { state = walk; }

			dx = speed;

			facingRight = true;
		}
		else {
			dx = 0;

			if (onGround) {
				state = stay;
			}
		}

		
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			canJump = true;
		}
		if (countOfJump > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
			--countOfJump;
			dy = -Final::jumpForce; onGround = false;
			if (countOfJump == 1) {
				state = jump;
			}
			else if (countOfJump == 0) {
				state = doubleJump;
			}
			canJump = false;
		}
	}
	else {
		setSpeed(0);
		state = death;
		time = 0;
		dx = 0; dy = 0;
	}
}
bool Player::checkBoundsOfMap(float Dx, float Dy, Level *lvl) {
	for (int i = yPos / Final::tilesRezolution; i < (yPos + Final::playerRezolution) / Final::tilesRezolution; ++i) 
	for (int j = xPos / Final::tilesRezolution; j < (xPos + Final::playerRezolution) / Final::tilesRezolution; ++j) {
		if (lvl->getTileMap()[i][j] == '0' || lvl->getTileMap()[i][j] == '1' || lvl->getTileMap()[i][j] == '2' || lvl->getTileMap()[i][j] == '3' ||
			lvl->getTileMap()[i][j] == '4' || lvl->getTileMap()[i][j] == '5' || lvl->getTileMap()[i][j] == '6' || lvl->getTileMap()[i][j] == '7' || lvl->getTileMap()[i][j] == '8') {

			if (Dy > 0.f) { setPosY(i * Final::tilesRezolution - Final::playerRezolution); dy = 0; onGround = true; countOfJump = Final::countOfJumps; }
			if (Dy < 0.f) { setPosY((i - 1) * Final::tilesRezolution + Final::playerRezolution); dy = 0; state = fall; }

			if (Dx > 0.f) { setPosX(j * Final::tilesRezolution - Final::playerRezolution); dx = 0; }
			if (Dx < 0.f) { setPosX((j - 1) * Final::tilesRezolution + Final::playerRezolution); dx = 0; }

		}
		else {
			if (Dy > 0.15f) {
				onGround = false; state = fall;
				if (countOfJump == Final::countOfJumps) {
					--countOfJump;
				}
			}
		}

		if (lvl->getTileMap()[i][j] == 'F') {
			//animation
			
			lvl->getTileMap()[i][j] = ' ';

			++currentLevel;
		}
		if (lvl->getTileMap()[i][j] == 'W') {
			//animation

			return true;
			lvl->getTileMap()[i][j] = ' ';

		}

	}

	return 0;
}

int Player::getScore() {
	return playerScore;
}