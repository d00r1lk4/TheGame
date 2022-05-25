#pragma once

#include "Entity.h"
#include "Berries.h"
#include "Traps.h"

#include "Checkpoint.h"
#include "NextLevel.h"

#include <iostream>

class PhysicsEngine {
private:
	bool nextLevel = false;

public:
	PhysicsEngine() {}

	void Collision(std::list<Entity*>& entities, std::list<Berries*>& berries, std::list<Traps*>& traps, Checkpoint*& const finish) {
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

		std::list<Berries*>::iterator berriesIterator;
		for (berriesIterator = berries.begin(); berriesIterator != berries.end(); ++berriesIterator) {
			if ((*berriesIterator)->getRect().intersects(player->getRect()) && player->checkAlive() && !(*berriesIterator)->checkCollected()) {
				player->setScore(player->getScore() + 100);
				(*berriesIterator)->collect();
			}
		}

		std::list<Traps*>::iterator trapsIterator;
		for (trapsIterator = traps.begin(); trapsIterator != traps.end(); ++trapsIterator) {
			if ((*trapsIterator)->getRect().intersects(player->getRect()) && player->checkAlive()) {
				player->dead();
			}
		}

		if (finish->getRect().intersects(player->getRect())) {
			if (finish) {
				if (finish->toString() == "NextLevel" && !nextLevel) {
					NextLevel* next = dynamic_cast<NextLevel*>(finish);
					if (next->canGo()) {
						//addAnim
						player->nextLevel();
						nextLevel = true;
					}
				}
				else if (finish->toString() == "Finish") {
					//add anim
					//final scene
				}
			}
		}

	}
	void Update(
		float time,
		std::list<Entity*>& entities,
		std::list<Berries*>& berries,
		std::list<Traps*>& traps,
		Checkpoint*& const finish,
		Level *lvl	)
	{
		std::list<Entity*>::iterator entitiesIterator;
		Player* player = dynamic_cast<Player*>(entities.front());
		//UPDATE
		player->update(time, lvl);
		for (entitiesIterator = ++entities.begin(); entitiesIterator != entities.end(); ++entitiesIterator) {
			(*entitiesIterator)->update(time, lvl);
		}

		std::list<Berries*>::iterator berriesIterator;
		for (berriesIterator = berries.begin(); berriesIterator != berries.end(); ++berriesIterator) {
			(*berriesIterator)->update(time);
		}

		std::list<Traps*>::iterator trapsIterator;
		for (trapsIterator = traps.begin(); trapsIterator != traps.end(); ++trapsIterator) {
			(*trapsIterator)->update(time);
		}

		if (finish) {
			finish->update(time);
		}
		//
	}
};