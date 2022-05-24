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
	virtual void checkBoundsOfMap(float Dx, float Dy) {};


	Enemy(sf::String file, float x, float y, float width, float height) : Entity(setImage(file), x, y, width, height) {}


public:
	virtual void update(float time) {};
	
	virtual sf::String toString() {
		return "Enemy";
	}
};