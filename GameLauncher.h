#pragma once

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "Level.h"

#include <iostream>

#include "Player.h"
#include "Entity.h"

#include "Berries.h"

#include <vector>
#include <list>
#include <vector>


#include "testMap.h"
#include "testMap2.h"

std::vector<Level*> setLevels() {
	std::vector<Level*> levels {};

	levels.push_back(new Level(TESTTileMap, HEIGTH_TESTMAP, WIDTH_TESTMAP, 200));
	levels.push_back(new Level(TESTTileMap2, HEIGTH_TESTMAP2, WIDTH_TESTMAP2, 150));




	return levels;
}

class GameLauncher {
private:
	sf::RenderWindow* window;

	sf::Clock gameUpdateClock;
	sf::Clock Timer;

	int pause = 0;
	bool spamESC = false;


	float checkPause() {
		float time = gameUpdateClock.getElapsedTime().asMicroseconds();
		gameUpdateClock.restart();
		time /= Final::gameSpeed;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !spamESC) {
			++pause;
			spamESC = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			spamESC = false;
		}


		if (pause % 2 == 1) {
			time = 0;
		}

		return time;
	}

	bool checkExit() {
		return (pause % 2 == 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
	}


public:
	GameLauncher(sf::RenderWindow *window) : window(window) { }

	void LaunchGame() {
		std::vector<Level*> levels = setLevels();
		std::list<Entity*> entities = levels[Level::getCurrentLevel()]->getEntities();
		std::list<Berries*> berries = levels[Level::getCurrentLevel()]->getBerries();
		std::list<Traps*> traps = levels[Level::getCurrentLevel()]->getTraps();

		Player* player;

		//
		while (!checkExit()) {
			float time = checkPause();

			player = dynamic_cast<Player*>(entities.front());

			if (player->checkAlive() && (pause % 2) == 0) { levels[Level::getCurrentLevel()]->updateTime(Timer.getElapsedTime().asSeconds()); }
			Timer.restart();

			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					break;
				}
				if (event.type == sf::Event::Resized) {
					//window->setPosition(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2));
					window->setSize(sf::Vector2u(600, 600));
				}

				if (event.type == sf::Event::LostFocus) {
					pause = 1;
				}


				if (event.type == sf::Event::KeyPressed) {
					if(/*!player->checkAlive() && */sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
						levels[Level::getCurrentLevel()]->reload(entities, berries, traps, levels, player->getScore());
					}
				}
					
			}
			

			levels[Level::getCurrentLevel()]->Next(entities, berries, traps, levels);

			GameEngine::Physics.Collision(entities, berries, traps);
			GameEngine::Physics.Update(time, entities, berries, traps, levels[Level::getCurrentLevel()]);


			GameEngine::GraphicsRender.Render(*window, levels[Level::getCurrentLevel()], entities, berries, traps, time);
		}

		for (auto &elem : levels) {
			delete elem;
		}
		levels.clear();

		for (auto &elem : entities) {
			delete elem;
		}
		entities.clear();

		for (auto &elem : berries) {
			delete elem;
		}
		berries.clear();

		for (auto &elem : traps) {
			delete elem;
		}
		traps.clear();

		Level::reset();
		
		return;
	}

};