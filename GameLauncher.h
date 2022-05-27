#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameEngine.h"
#include "Level.h"

#include <iostream>

#include "Player.h"
#include "Entity.h"

#include "Berries.h"

#include <vector>
#include <list>
#include <vector>


//#include "testMap.h"
//#include "testMap2.h"
//#include "testMap3.h"

#include "FirstLevel.h"
#include "SecondLevel.h"
#include "ThirdLevel.h"

std::vector<Level*> setLevels() {
	std::vector<Level*> levels {};

	//levels.push_back(new Level(TESTTileMap, TESTFinishTileMap, HEIGTH_TESTMAP, WIDTH_TESTMAP, 200));
	//levels.push_back(new Level(TESTTileMap2, TESTFinishTileMap2, HEIGTH_TESTMAP2, WIDTH_TESTMAP2, 150));
	//levels.push_back(new Level(TESTTileMap3, TESTFinishTileMap3, HEIGTH_TESTMAP3, WIDTH_TESTMAP3, 100));
	 
	levels.push_back(new Level(FirstTileMap, FirstFinishTileMap, Final::HEIGTH_LEVEL, Final::WIDTH_LEVEL, 60));
	levels.push_back(new Level(SecondTileMap, SecondFinishTileMap, Final::HEIGTH_LEVEL, Final::WIDTH_LEVEL, 60));
	levels.push_back(new Level(ThirdTileMap, ThirdFinishTileMap, Final::HEIGTH_LEVEL, Final::WIDTH_LEVEL, 60));



	return levels;
}

class GameLauncher {
private:
	sf::RenderWindow* window;

	sf::Music music;

	sf::Clock gameUpdateClock;
	sf::Clock Timer;

	int pause = 0;
	bool spamESC = false;

	bool isExit = false;

	//pause audio
	float checkPause(sf::Music &music) {
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
			music.pause();
		}
		if ((music.getStatus() == sf::Music::Paused) && time != 0) {
			music.play();
		}


		return time;
	}

	bool checkExit() {
		isExit = true;
		return (pause % 2 == 1) && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
	}


public:
	GameLauncher(sf::RenderWindow *window) : window(window) {
		music.openFromFile("sounds/levelMusic.ogg");
		music.setVolume(10);
		music.play();
		music.setLoop(1);
	}

	bool LaunchGame(int &playerScore) {
		std::vector<Level*> levels = setLevels();
		std::list<Entity*> entities = levels[Level::getCurrentLevel()]->getEntities();
		std::list<Berries*> berries = levels[Level::getCurrentLevel()]->getBerries();
		std::list<Traps*> traps = levels[Level::getCurrentLevel()]->getTraps();

		Player* player = dynamic_cast<Player*>(entities.front());

		//
		while (!checkExit()) {
			float time = checkPause(music);

			player = dynamic_cast<Player*>(entities.front());

			if (player->checkAlive() && (pause % 2) == 0) { levels[Level::getCurrentLevel()]->updateTime(Timer.getElapsedTime().asSeconds()); }
			Timer.restart();

			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					return false;
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
			levels[Level::getCurrentLevel()]->Update(entities);

			GameEngine::Physics.Collision(entities, berries, traps);
			if (GameEngine::Physics.Update(time, entities, berries, traps, levels[Level::getCurrentLevel()])) {
				isExit = false;
				break;
			}

			GameEngine::GraphicsRender.Render(*window, levels[Level::getCurrentLevel()], entities, berries, traps, time);
		}

		playerScore = player->getScore();

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
		
		music.stop();
		return isExit ? false : true;
	}

};