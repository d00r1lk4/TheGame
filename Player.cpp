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

	health = 1;

	sprite.setTextureRect(sf::IntRect(0, 0, Final::playerRezolution, Final::playerRezolution));

	walkBuffer.loadFromFile("sounds/playerFootstep.ogg");
	walkSound.setBuffer(walkBuffer);
	walkSound.setVolume(100);
	walkSound.setLoop(1);
	walkSound.pause();
}


bool Player::update(float time, Level *lvl) {
	controller(time);

	switch (state) {
	case walk: {
		Animator.Play("walk", time); break;
	}
	case jump: {
		Animator.Play("jump", time); break;
	}
	case fall: {
		Animator.Play("fall", time); break;
	}
	case doubleJump: {
		Animator.Play("doubleJump", time); break;
	}
	case wallJump: {
		Animator.Play("wallJump", time); break;
	}
	case stay: {
		Animator.Play("stay", time); break;
	}
	case death: {
		Animator.Play("death", time); break;
	}

	}

	bool finish = 0;

	xPos += dx * time;
	finish = checkBoundsOfMap(dx, 0, lvl);

	dy += Final::gravitation * time;
	yPos += dy * time;
	finish = checkBoundsOfMap(0, dy, lvl);

	sprite.setPosition(xPos + sprite.getGlobalBounds().width / 2, yPos + sprite.getGlobalBounds().height / 2);

	if (health <= 0 && !isPlayed) {
		dead();
		state = death;

		soundBuffer.loadFromFile("sounds/playerDied.ogg");
		sound.setBuffer(soundBuffer);
		sound.setVolume(100);
		sound.play();

		isPlayed = true;
	}

	return finish;
}




void Player::controller(float time) {
	if (isAlive) {
		if (state == walk) {
			if (!isWalk) {
				walkSound.play(); isWalk = true;
			}
		}
		else {
			stopSounds();
		}

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

				soundBuffer.loadFromFile("sounds/jump.ogg");
				sound.setBuffer(soundBuffer);
				sound.setVolume(100);
				sound.play();
			}
			else if (countOfJump == 0) {
				state = doubleJump;

				soundBuffer.loadFromFile("sounds/doubleJump.ogg");
				sound.setBuffer(soundBuffer);
				sound.setVolume(100);
				sound.play();
			}
			canJump = false;
		}
	}
	else {
		setSpeed(0);
		state = death;
		time = 0;
		dx = 0; dy = 0;

		stopSounds();
	}
}
bool Player::checkBoundsOfMap(float Dx, float Dy, Level *lvl) {
	for (int i = yPos / Final::tilesRezolution; i < (yPos + Final::playerRezolution) / Final::tilesRezolution; ++i) 
	for (int j = xPos / Final::tilesRezolution; j < (xPos + Final::playerRezolution) / Final::tilesRezolution; ++j) {
			//
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

			lvl->getTileMap()[i][j] == '}' || lvl->getTileMap()[i][j] == '~' || lvl->getTileMap()[i][j] == 'X' ||
			//

			//
			lvl->getTileMap()[i][j] == 'Y' || lvl->getTileMap()[i][j] == 'Z' || lvl->getTileMap()[i][j] == '[' ||
			lvl->getTileMap()[i][j] == 'd' || lvl->getTileMap()[i][j] == ']' || lvl->getTileMap()[i][j] == '_'
			//
			) {

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

			stopSounds();

			return true;

		}

	}

	return 0;
}

int Player::getScore() {
	return playerScore;
}

void Player::stopSounds() {
	walkSound.pause();
	isWalk = false;
}