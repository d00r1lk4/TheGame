#include "Level.h"

#include <SFML\Graphics.hpp>
#include <iostream>

class Entity;

#include "Player.h"
#include "AngryPig.h"
#include "BlueBird.h"

#include "Cherries.h"
#include "Strawberry.h"
#include "Apple.h"

#include "Spike.h"

#include <list>
#include <vector>

int Level::currentLevel = 0;

void Level::copyLevel(sf::String* to, const sf::String* from) {
	for (int i = 0; i < HEIGTH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			to[i].insert(j, from[i][j]);
		}
	}
}
Level::Level(const sf::String* TileMap, const sf::String* FinishTileMap, int h, int w, float time) : ConstGameTime(time) {
	HEIGTH = h;
	WIDTH = w;

	this->ConstTileMap = new sf::String[h];
	this->TileMap = new sf::String[h];

	this->ConstFinishTileMap = new sf::String[h];

	copyLevel(this->ConstTileMap, TileMap);
	copyLevel(this->TileMap, TileMap);
	copyLevel(this->ConstFinishTileMap, FinishTileMap);

	gameTime = time;
}

std::list<Entity*> Level::getEntities() {
	std::list<Entity*> entities;
	//Player and Enemy
	int* xPos = new int(0), * yPos = new int(0);
	for (int i = 0; i < HEIGTH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (TileMap[i][j] == 'P') {
				TileMap[i][j] = ' ';
				*xPos = j * Final::tilesRezolution;
				*yPos = i * Final::tilesRezolution;
			}
			if (TileMap[i][j] == 'p') {
				TileMap[i][j] = ' ';
				entities.push_back(new AngryPig(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
			if (TileMap[i][j] == 'b') {
				TileMap[i][j] = ' ';
				entities.push_back(new BlueBird(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
		}
	}

	entities.push_front(new Player(*xPos, *yPos));
	delete xPos, yPos;
	//

	return entities;
}
std::list<Berries*> Level::getBerries() {
	std::list<Berries*> berries;
	for (int i = 0; i < HEIGTH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (TileMap[i][j] == 'c') {
				TileMap[i][j] = ' ';
				berries.push_back(new Cherries(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
			if (TileMap[i][j] == 's') {
				TileMap[i][j] = ' ';
				berries.push_back(new Strawberry(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
			if (TileMap[i][j] == 'a') {
				TileMap[i][j] = ' ';
				berries.push_back(new Apple(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
		}
	}

	return berries;
}
std::list<Traps*> Level::getTraps() {
	std::list<Traps*> traps;
	for (int i = 0; i < HEIGTH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (TileMap[i][j] == '^') {
				TileMap[i][j] = ' ';
				traps.push_back(new Spike(j * Final::tilesRezolution, i * Final::tilesRezolution + 2));
			}
		}
	}

	return traps;
}

void Level::Next(std::list<Entity*> &entities, std::list<Berries*>& berries, std::list<Traps*>& traps, std::vector<Level*> &levels) {
	Player* player = dynamic_cast<Player*>(entities.front());
	if (currentLevel != player->getCurrentLevel()) {
		int score = player->getScore();
		currentLevel = player->getCurrentLevel();
		clearEntities(entities);
		clearBerries(berries);
		clearTraps(traps);

		entities = levels[Level::getCurrentLevel()]->getEntities();
		berries = levels[Level::getCurrentLevel()]->getBerries();
		traps = levels[Level::getCurrentLevel()]->getTraps();

		player = dynamic_cast<Player*>(entities.front());
		player->setScore(score);
		player->setLevel(Level::getCurrentLevel());
	}
}

void Level::Update(std::list<Entity*>& entities) {
	std::list<Entity*>::iterator entitiesIterator;
	for (entitiesIterator = ++entities.begin(); entitiesIterator != entities.end(); ++entitiesIterator) {
		if ((*entitiesIterator)->checkAlive()) {
			return;
		}
	}

	copyLevel(TileMap, ConstFinishTileMap);

}


void Level::clearEntities(std::list<Entity*>& entities) {
	for (auto elem : entities) {
		delete elem;
	}
	entities.clear();
}
void Level::clearBerries(std::list<Berries*>& berries) {
	for (auto elem : berries) {
		delete elem;
	}
	berries.clear();
}
void Level::clearTraps(std::list<Traps*>& traps) {
	for (auto elem : traps) {
		delete elem;
	}
	traps.clear();
}

void Level::reload(std::list<Entity*>& entities, std::list<Berries*>& berries, std::list<Traps*>& traps, std::vector<Level*>& levels, int score) {
	isRealod = true;

	clearEntities(entities);
	clearBerries(berries);
	clearTraps(traps);

	copyLevel(this->TileMap, this->ConstTileMap);

	entities = levels[Level::getCurrentLevel()]->getEntities();
	berries = levels[Level::getCurrentLevel()]->getBerries();
	traps = levels[Level::getCurrentLevel()]->getTraps();

	Player* player = dynamic_cast<Player*>(entities.front());

	player->setLevel(Level::getCurrentLevel());
	
	if (score >= 250) {
		player->setScore(score - 250);
	}
	else {
		player->setScore(0);
	}

	gameTime = ConstGameTime;
}