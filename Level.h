#pragma once

#include <list>

#include <SFML/Graphics.hpp>

class Entity;
class Berries;
class Traps;

class Level {
private:
	static int currentLevel;

	int HEIGTH = 0;
	int WIDTH = 0;

	sf::String *TileMap = nullptr;
	sf::String *ConstTileMap = nullptr;

	const float ConstGameTime;
	float gameTime = 0;

	bool isRealod = false;


	void copyLevel(sf::String* first, const sf::String* second);

	void clearObjects(std::list<Entity*>& entities);

public:
	bool isReloading = false;
	static bool isExit;

	Level(const sf::String* TileMap, int h, int w, float time);

	std::list<Entity*> getEntities();
	std::list<Berries*> getBerries();
	std::list<Traps*> getTraps();

	float getTime() {
		return gameTime;
	}
	void updateTime(float time) {
		gameTime -= time;
	}

	void Update(std::list<Entity*>& entities, std::vector<Level*>& levels);


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
	void reload(std::list<Entity*>& entities, std::vector<Level*>& levels, int score);

	static int getCurrentLevel() {
		return currentLevel;
	}
	static void reset() {
		isExit = true;
		currentLevel = 0;
	}

};