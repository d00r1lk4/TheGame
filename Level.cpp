#include "Level.h"

#include <SFML\Graphics.hpp>
#include <iostream>

class Entity;

#include "Player.h"
#include "AngryPig.h"
#include "BlueBird.h"

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
Level::Level(const sf::String* TileMap, int h, int w, float time) : ConstGameTime(time) {
	HEIGTH = h;
	WIDTH = w;

	this->ConstTileMap = new sf::String[h];
	this->TileMap = new sf::String[h];

	copyLevel(this->ConstTileMap, TileMap);
	copyLevel(this->TileMap, TileMap);

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

void Level::Update(std::list<Entity*> &entities, std::vector<Level*> &levels) {
	Player* player = dynamic_cast<Player*>(entities.front());
	if (currentLevel != player->getCurrentLevel()) {
		int score = player->getScore();
		currentLevel = player->getCurrentLevel();
		clearObjects(entities);

		entities = levels[currentLevel]->getEntities();

		player = dynamic_cast<Player*>(entities.front());
		player->setScore(score);
		player->setLevel(Level::getCurrentLevel());
	}
}

void Level::clearObjects(std::list<Entity*>& entities) {
	for (auto elem : entities) {
		delete elem;
	}
	entities.clear();
}
void Level::reload(std::list<Entity*>& entities, std::vector<Level*>& levels, int score) {
	isRealod = true;

	clearObjects(entities);

	copyLevel(this->TileMap, this->ConstTileMap);

	entities = levels[Level::getCurrentLevel()]->getEntities();
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