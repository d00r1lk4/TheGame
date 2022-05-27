#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <sstream>

#include "Level.h"

#include "Entity.h"
#include "Player.h"

#include "Berries.h"

#include "Traps.h"

#include "Constants.h"

#include "Camera.h"

class GraphicsRenderingEngine {
private:
	sf::Font font;
	sf::Text playerScoreText;
	sf::Text timerText;

	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture pauseTexture;
	sf::Sprite pauseSprite;
	sf::Text pauseText;
	sf::Text exitText;

	float currentFrame = 0;

	void setTextSettings(sf::String fontPath) {
		font.loadFromFile(fontPath);

		playerScoreText.setString("");
		playerScoreText.setFont(font);
		playerScoreText.setCharacterSize(16);
		playerScoreText.setColor(sf::Color::White);

		timerText.setString("");
		timerText.setFont(font);
		timerText.setCharacterSize(16);
		timerText.setColor(sf::Color::White);

		pauseText.setString("pause");
		pauseText.setFont(font);
		pauseText.setCharacterSize(32);
		pauseText.setColor(sf::Color::White);
		pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);

		exitText.setString("press Backspace to exit the main menu...");
		exitText.setFont(font);
		exitText.setCharacterSize(16);
		exitText.setColor(sf::Color::White);
		exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
	}

	sf::String setRandomBackground() {
		srand((unsigned int)time(NULL));
		int backgroundRandom = rand() % 7;

		switch (backgroundRandom)
		{
		case 0: return "Blue.png";
		case 1: return "Brown.png";
		case 2: return "Gray.png";
		case 3: return "Green.png";
		case 4: return "Pink.png";
		case 5: return "Purple.png";
		case 6: return "Yellow.png";
		default: return "Blue.png";
		}
	}
	void setMapSettings(sf::String terrainPath, sf::String backgroundPath) {
		mapTexture.loadFromFile(terrainPath);
		mapSprite.setTexture(mapTexture);

		backgroundTexture.loadFromFile(backgroundPath + setRandomBackground());
		backgroundSprite.setTexture(backgroundTexture);
	}

	void RenderBackGround(sf::RenderWindow& window, Level* lvl) {
		for (int i = 0, backGroundCounti = 0; i < lvl->getHeigth(); ++i, ++backGroundCounti) {
			for (int j = 1, backGroundCountj = 0; j < lvl->getWidth(); ++j, ++backGroundCountj) {
				if (lvl->checkReload()) {
					backgroundTexture.loadFromFile("images/Background/" + setRandomBackground());
					lvl->checkReload() = false;
				}
				backgroundSprite.setTextureRect(sf::IntRect(Final::tilesRezolution * (backGroundCountj % 4),
					Final::tilesRezolution * (backGroundCounti % 4),
					Final::tilesRezolution,
					Final::tilesRezolution));

				backgroundSprite.setPosition(j * Final::tilesRezolution, i * Final::tilesRezolution);
				window.draw(backgroundSprite);
			}
		}
	}
	void RenderMap(sf::RenderWindow& window, Level *lvl, float time) {
		currentFrame += Final::animationSpeed * time;
		if (currentFrame > 10) { currentFrame = 0; }

		for (int i = 0, backGroundCounti = 0; i < lvl->getHeigth(); ++i, ++backGroundCounti) {
			for (int j = 0, backGroundCountj = 0; j < lvl->getWidth(); ++j, ++backGroundCountj) {
				if (lvl->getTileMap()[i][j] == ' ') { mapSprite.setTextureRect(sf::IntRect(304, 0, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '`') { mapSprite.setTextureRect(sf::IntRect(320, 0, 16, 16)); }

				//dark bricks
				if (lvl->getTileMap()[i][j] == 'f') { mapSprite.setTextureRect(sf::IntRect(0, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '(') { mapSprite.setTextureRect(sf::IntRect(16, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == ')') { mapSprite.setTextureRect(sf::IntRect(32, 32, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '$') { mapSprite.setTextureRect(sf::IntRect(0, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '%') { mapSprite.setTextureRect(sf::IntRect(16, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '&') { mapSprite.setTextureRect(sf::IntRect(32, 16, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '!') { mapSprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'e') { mapSprite.setTextureRect(sf::IntRect(16, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '#') { mapSprite.setTextureRect(sf::IntRect(32, 0, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '*') { mapSprite.setTextureRect(sf::IntRect(48, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '+') { mapSprite.setTextureRect(sf::IntRect(64, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == ',') { mapSprite.setTextureRect(sf::IntRect(48, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '-') { mapSprite.setTextureRect(sf::IntRect(64, 16, 16, 16)); }
				//

				//red bricks
				if (lvl->getTileMap()[i][j] == 'Y') { mapSprite.setTextureRect(sf::IntRect(272, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'Z') { mapSprite.setTextureRect(sf::IntRect(288, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '[') { mapSprite.setTextureRect(sf::IntRect(304, 32, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'd') { mapSprite.setTextureRect(sf::IntRect(272, 48, 16, 16)); }
				if (lvl->getTileMap()[i][j] == ']') { mapSprite.setTextureRect(sf::IntRect(288, 48, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '_') { mapSprite.setTextureRect(sf::IntRect(304, 48, 16, 16)); }
				//

				//green grass
				if (lvl->getTileMap()[i][j] == '0') { mapSprite.setTextureRect(sf::IntRect(96, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '1') { mapSprite.setTextureRect(sf::IntRect(112, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '2') { mapSprite.setTextureRect(sf::IntRect(128, 32, 16, 16)); }
								  
				if (lvl->getTileMap()[i][j] == '3') { mapSprite.setTextureRect(sf::IntRect(96, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '4') { mapSprite.setTextureRect(sf::IntRect(112, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '5') { mapSprite.setTextureRect(sf::IntRect(128, 16, 16, 16)); }
								  
				if (lvl->getTileMap()[i][j] == '6') { mapSprite.setTextureRect(sf::IntRect(96, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '7') { mapSprite.setTextureRect(sf::IntRect(112, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '8') { mapSprite.setTextureRect(sf::IntRect(128, 0, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '9') { mapSprite.setTextureRect(sf::IntRect(144, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == ':') { mapSprite.setTextureRect(sf::IntRect(160, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == ';') { mapSprite.setTextureRect(sf::IntRect(144, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '<') { mapSprite.setTextureRect(sf::IntRect(160, 16, 16, 16)); }
				//

				//yellow grass
				if (lvl->getTileMap()[i][j] == 'A') { mapSprite.setTextureRect(sf::IntRect(192, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'B') { mapSprite.setTextureRect(sf::IntRect(208, 32, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'C') { mapSprite.setTextureRect(sf::IntRect(224, 32, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '>') { mapSprite.setTextureRect(sf::IntRect(192, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '?') { mapSprite.setTextureRect(sf::IntRect(208, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '@') { mapSprite.setTextureRect(sf::IntRect(224, 16, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '.') { mapSprite.setTextureRect(sf::IntRect(192, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '/') { mapSprite.setTextureRect(sf::IntRect(208, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '=') { mapSprite.setTextureRect(sf::IntRect(224, 0, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'D') { mapSprite.setTextureRect(sf::IntRect(240, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'E') { mapSprite.setTextureRect(sf::IntRect(256, 0, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'V') { mapSprite.setTextureRect(sf::IntRect(240, 16, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'G') { mapSprite.setTextureRect(sf::IntRect(256, 16, 16, 16)); }
				//

				//wood
				if (lvl->getTileMap()[i][j] == 'N') { mapSprite.setTextureRect(sf::IntRect(0, 96, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'O') { mapSprite.setTextureRect(sf::IntRect(16, 96, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'Q') { mapSprite.setTextureRect(sf::IntRect(32, 96, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'K') { mapSprite.setTextureRect(sf::IntRect(0, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'L') { mapSprite.setTextureRect(sf::IntRect(16, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'M') { mapSprite.setTextureRect(sf::IntRect(32, 80, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'H') { mapSprite.setTextureRect(sf::IntRect(0, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'I') { mapSprite.setTextureRect(sf::IntRect(16, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'J') { mapSprite.setTextureRect(sf::IntRect(32, 64, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'R') { mapSprite.setTextureRect(sf::IntRect(48, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'S') { mapSprite.setTextureRect(sf::IntRect(64, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'T') { mapSprite.setTextureRect(sf::IntRect(48, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'U') { mapSprite.setTextureRect(sf::IntRect(64, 80, 16, 16)); }
				//

				//golden box
				if (lvl->getTileMap()[i][j] == 'g') { mapSprite.setTextureRect(sf::IntRect(192, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'h') { mapSprite.setTextureRect(sf::IntRect(208, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'i') { mapSprite.setTextureRect(sf::IntRect(224, 64, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'j') { mapSprite.setTextureRect(sf::IntRect(192, 80, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'k') { mapSprite.setTextureRect(sf::IntRect(208, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'l') { mapSprite.setTextureRect(sf::IntRect(224, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'n') { mapSprite.setTextureRect(sf::IntRect(208, 96, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'o') { mapSprite.setTextureRect(sf::IntRect(224, 96, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'q') { mapSprite.setTextureRect(sf::IntRect(240, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'r') { mapSprite.setTextureRect(sf::IntRect(240, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 't') { mapSprite.setTextureRect(sf::IntRect(240, 96, 16, 16)); }
				//

				//golden box
				if (lvl->getTileMap()[i][j] == 'u') { mapSprite.setTextureRect(sf::IntRect(272, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'v') { mapSprite.setTextureRect(sf::IntRect(288, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'w') { mapSprite.setTextureRect(sf::IntRect(304, 64, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'x') { mapSprite.setTextureRect(sf::IntRect(272, 80, 16, 16)); }

				if (lvl->getTileMap()[i][j] == 'y') { mapSprite.setTextureRect(sf::IntRect(288, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'z') { mapSprite.setTextureRect(sf::IntRect(304, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '{') { mapSprite.setTextureRect(sf::IntRect(288, 96, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '|') { mapSprite.setTextureRect(sf::IntRect(304, 96, 16, 16)); }

				if (lvl->getTileMap()[i][j] == '}') { mapSprite.setTextureRect(sf::IntRect(320, 64, 16, 16)); }
				if (lvl->getTileMap()[i][j] == '~') { mapSprite.setTextureRect(sf::IntRect(320, 80, 16, 16)); }
				if (lvl->getTileMap()[i][j] == 'X') { mapSprite.setTextureRect(sf::IntRect(320, 96, 16, 16)); }
				//

				if (lvl->getTileMap()[i][j] == 'F' || lvl->getTileMap()[i][j] == 'W') {
					mapSprite.setTextureRect(sf::IntRect(18 * static_cast<int>(currentFrame), 112, 16, 16));
				}

				mapSprite.setPosition(j * Final::tilesRezolution, i * Final::tilesRezolution);
				window.draw(mapSprite);
			}
		}
		//
	}
	void RenderTimers(sf::RenderWindow &window, Entity *entity, float gameTime) {
		Player *player = dynamic_cast<Player*>(entity);

		std::ostringstream playerScoreString, levelTimerString;
		playerScoreString << player->getScore(); levelTimerString << (int)gameTime;

		if (player->getScore() < 10) {
			playerScoreText.setString("Score: 0000" + playerScoreString.str());
		}
		else if (player->getScore() < 100) {
			playerScoreText.setString("Score: 000" + playerScoreString.str());
		}
		else if (player->getScore() < 1000) {
			playerScoreText.setString("Score: 00" + playerScoreString.str());
		}
		else if (player->getScore() < 10000) {
			playerScoreText.setString("Score: 0" + playerScoreString.str());
		}
		else {
			playerScoreText.setString("Score: " + playerScoreString.str());
		}

		if (gameTime <= 0) {
			player->dead();
		}
		else if (gameTime < 10) {
			timerText.setString("Time: 00" + levelTimerString.str());
		}
		else if (gameTime < 100) {
			timerText.setString("Time: 0" + levelTimerString.str());
		}
		else if (gameTime < 1000) {
			timerText.setString("Time: " + levelTimerString.str());
		}
		//

		playerScoreText.setPosition(playerCamera.getCenter().x - 100, playerCamera.getCenter().y - 290);
		timerText.setPosition(playerCamera.getCenter().x + 100, playerCamera.getCenter().y - 290);

		window.draw(playerScoreText);
		window.draw(timerText);
	}


	void RenderEntities(sf::RenderWindow &window, std::list<Entity*> &entities) {
		std::list<Entity*>::iterator entityIterator;
		for (entityIterator = entities.begin(); entityIterator != entities.end(); ++entityIterator) {
			window.draw((*entityIterator)->getSprite());
		}
	}
	void RenderBerries(sf::RenderWindow &window, std::list<Berries*> &berries) {
		std::list<Berries*>::iterator berriesIterator;
		for (berriesIterator = berries.begin(); berriesIterator != berries.end(); ++berriesIterator) {
			window.draw((*berriesIterator)->getSprite());
		}
	}
	void RenderTraps(sf::RenderWindow& window, std::list<Traps*>& traps) {
		std::list<Traps*>::iterator trapsIterator;
		for (trapsIterator = traps.begin(); trapsIterator != traps.end(); ++trapsIterator) {
			window.draw((*trapsIterator)->getSprite());
		}
	}

	///////
	void RanderParticles(sf::RenderWindow &window, Entity* entity) {
		Player* player = dynamic_cast<Player*>(entity);

		sf::Sprite particles[4];
		sf::Texture partsTexture;
		partsTexture.loadFromFile("D:/SFML/TheGame/TheGame/images/Other/Dust Particle.png");

		for (auto elem : particles) {
			elem.setTexture(partsTexture);
			elem.setPosition(player->getPosX() + 16, player->getPosY() + 16);
		}

		if (!player->checkGround()) {
			for (auto elem : particles) {
				window.draw(elem);
			}
		}

	}
	
public:
	GraphicsRenderingEngine() {
		setTextSettings("fonts/pixel.ttf");
		setMapSettings("images/Terrain/Terrain (16x16).png", "images/Background/");

		pauseTexture.loadFromFile("images/Other/Black.png");
		pauseSprite.setTexture(pauseTexture);
		pauseSprite.setOrigin(16.f / 2, 16.f / 2);
		pauseSprite.setColor(sf::Color(255, 255, 255, 100));
		pauseSprite.setScale(38, 38);


		//playerCamera.reset(sf::FloatRect(-60, -70, Final::rezolution, Final::rezolution));
		playerCamera.reset(sf::FloatRect(-60, -170, Final::rezolution, Final::rezolution));
	}

	void Render(sf::RenderWindow &window, Level *lvl, std::list<Entity*> &entities, std::list<Berries*>& berries, std::list<Traps*>& traps, float time) {
		window.clear(sf::Color(33, 31, 48));

		RenderBackGround(window, lvl);

		RenderEntities(window, entities);
		RenderBerries(window, berries);
		RenderTraps(window, traps);

		RenderMap(window, lvl, time);
		//RanderParticles(window, entities.front());

		if (entities.front()->checkAlive()) {
			//setPlayerPosForCamera(entities.front()->getSprite().getPosition().x, entities.front()->getSprite().getPosition().y);
			window.setView(playerCamera);
		}

		if (time != 0) {
			RenderTimers(window, entities.front(), lvl->getTime());
		}
		else {
			pauseSprite.setPosition(playerCamera.getCenter().x, playerCamera.getCenter().y);
			window.draw(pauseSprite);

			pauseText.setPosition(playerCamera.getCenter().x, playerCamera.getCenter().y);
			exitText.setPosition(playerCamera.getCenter().x, playerCamera.getCenter().y + 250);
			window.draw(pauseText);
			window.draw(exitText);
		}

		window.display();
	}

};