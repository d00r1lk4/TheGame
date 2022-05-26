#pragma once

#include "Entity.h"

class Enemy : public Entity {
private:
	sf::Image setImage(sf::String file) {
		sf::Image enemyImage;
		enemyImage.loadFromFile("images/Enemies/" + file);

		return enemyImage;

	}


protected:
	virtual bool checkBoundsOfMap(float Dx, float Dy) { return 0; };


	Enemy(sf::String file, float x, float y, float width, float height) : Entity(setImage(file), x, y, width, height) {}


public:
	virtual bool update(float time) { return 0; };
	
	virtual sf::String toString() {
		return "Enemy";
	}
};