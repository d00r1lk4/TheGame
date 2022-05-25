#pragma once

#include <list>

#include <SFML/Graphics.hpp>

class Entity;
class Berries;
class Traps;
class Checkpoint;

class Level {
private:
	static int currentLevel;

	int countOfEnemies;

	int HEIGTH = 0;
	int WIDTH = 0;

	sf::String *TileMap = nullptr;
	sf::String *ConstTileMap = nullptr;

	const float ConstGameTime;
	float gameTime = 0;

	bool isRealod = false;


	void copyLevel(sf::String* first, const sf::String* second);

	void clearEntities(std::list<Entity*>& entities);
	void clearBerries(std::list<Berries*>& berries);
	void clearTraps(std::list<Traps*>& traps);

public:
	bool isReloading = false;

	Level(const sf::String* TileMap, int h, int w, float time);

	std::list<Entity*> getEntities();
	std::list<Berries*> getBerries();
	std::list<Traps*> getTraps();
	Checkpoint *getFinish();

	float getTime() {
		return gameTime;
	}
	void updateTime(float time) {
		gameTime -= time;
	}

	void Next(std::list<Entity*>& entities, std::list<Berries*>& berries, std::list<Traps*>& traps, Checkpoint*& const finish, std::vector<Level*>& levels);


	int getHeigth() {
		return HEIGTH;
	}
	int getWidth() {
		return WIDTH;
	}

	sf::String* getTileMap() {
		return TileMap;
	}

	bool &checkReload() {
		return isRealod;
	}
	void reload(std::list<Entity*>& entities, std::list<Berries*>& berries, std::list<Traps*>& traps, Checkpoint*& const finish, std::vector<Level*>& levels, int score);

	static int getCurrentLevel() {
		return currentLevel;
	}
	static void reset() {
		currentLevel = 0;
	}

};