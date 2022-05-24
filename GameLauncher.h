#pragma once

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "Level.h"

#include <iostream>

#include "Player.h"

#include <vector>
#include <list>
#include <vector>

#include "AngryPig.h"

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
	sf::RenderWindow window;

	sf::Clock gameUpdateClock;
	sf::Clock Timer;

	sf::Image icon;

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

	void setWindowSettings() {
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		window.setFramerateLimit(60);

		window.setMouseCursorVisible(false);
	}

public:
	GameLauncher() {
		icon.loadFromFile("images/icon.png");
		window.create(sf::VideoMode(Final::rezolution, Final::rezolution), L"TheGame", sf::Style::Default);
		setWindowSettings();
	}

	void LaunchGame() {
		std::vector<Level*> levels = setLevels();
		std::list<Entity*> entities = levels[Level::getCurrentLevel()]->getEntities();
		Player* player;

		//


		while (window.isOpen()) {
			float time = checkPause();

			player = dynamic_cast<Player*>(entities.front());

			if (player->checkAlive() && (pause % 2) == 0) { levels[Level::getCurrentLevel()]->updateTime(Timer.getElapsedTime().asSeconds()); }
			Timer.restart();

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::Resized) {
					//window.setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
					window.setSize(sf::Vector2u(600, 600));
				}

				if (event.type == sf::Event::GainedFocus) {
					pause = 0;
				}
				if (event.type == sf::Event::LostFocus) {
					pause = 1;
				}


				if (event.type == sf::Event::KeyPressed) {
					if(/*!player->checkAlive() && */sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
						levels[Level::getCurrentLevel()]->reload(entities, levels, player->getScore());
					}
				}
					
			}
			

			levels[Level::getCurrentLevel()]->Update(entities, levels);

			GameEngine::Physics.Collision(entities);
			GameEngine::Physics.Update(time, entities, levels[Level::getCurrentLevel()]);


			GameEngine::GraphicsRender.Render(window, levels[Level::getCurrentLevel()], entities, time);
		}
	}

};