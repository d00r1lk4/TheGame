#pragma once

#include "Entity.h"

#include <iostream>

class PhysicsEngine {
private:


public:
	PhysicsEngine() {}

	void Collision(std::list<Entity*>& entities) {
		std::list<Entity*>::iterator entitiesIterator;
		Player* player = dynamic_cast<Player*>(entities.front());
		//collision with enemies
		for (entitiesIterator = ++entities.begin(); entitiesIterator != entities.end(); ++entitiesIterator) {
			if ((*entitiesIterator)->getRect().intersects(player->getRect()) && player->checkAlive() && (*entitiesIterator)->checkAlive()) {
				if (player->getDy() > 0) {
					player->setDy(-0.2f);
					(*entitiesIterator)->hit();
					player->giveJump();

					if ((*entitiesIterator)->toString() == "AngryPig") {
						player->setScore(player->getScore() + 75);
					}
					if ((*entitiesIterator)->toString() == "BlueBird") {
						player->setScore(player->getScore() + 100);
					}
				}
				else if (player->getDy() < -0.2f || player->checkGround()) {
					player->dead();
				}
			}
		}
		//
	}
	void Update(float time, std::list<Entity*>& entities, Level *lvl) {
		std::list<Entity*>::iterator entitiesIterator;
		Player* player = dynamic_cast<Player*>(entities.front());
		//UPDATE
		player->update(time, lvl);
		for (entitiesIterator = ++entities.begin(); entitiesIterator != entities.end(); ++entitiesIterator) {
			(*entitiesIterator)->update(time, lvl);
		}
		//
	}
};