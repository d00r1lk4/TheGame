#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "GameLauncher.h"

void events(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized) {
			//window->setPosition(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2));
			window.setSize(sf::Vector2u(600, 600));
		}

	}
}

void drawCongratulationsWindow(sf::RenderWindow& window, int score) {
	sf::Font font;
	font.loadFromFile("fonts/pixel.ttf");

	sf::Text congratsText;
	sf::Text scoreText;
	sf::Text thanksText;
	sf::Text pressEnterText;

	congratsText.setString("Congratulations!\tYou did it!");
	congratsText.setFont(font);
	congratsText.setCharacterSize(24);
	congratsText.setColor(sf::Color::White);
	congratsText.setOrigin(congratsText.getLocalBounds().width / 2, congratsText.getLocalBounds().height / 2);
	congratsText.setPosition(window.getSize().x / 2.f, 30);

	std::ostringstream playerScoreString;	playerScoreString << score;
	scoreText.setString("your score: " + playerScoreString.str());
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setColor(sf::Color::White);
	scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
	scoreText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	thanksText.setString("Thanks for playing!");
	thanksText.setFont(font);
	thanksText.setCharacterSize(24);
	thanksText.setColor(sf::Color::White);
	thanksText.setOrigin(thanksText.getLocalBounds().width / 2, thanksText.getLocalBounds().height / 2);
	thanksText.setPosition(window.getSize().x / 2.f, window.getSize().y - 80);

	pressEnterText.setString("press Enter to continue...");
	pressEnterText.setFont(font);
	pressEnterText.setCharacterSize(16);
	pressEnterText.setColor(sf::Color::White);
	pressEnterText.setOrigin(pressEnterText.getLocalBounds().width / 2, pressEnterText.getLocalBounds().height / 2);
	pressEnterText.setPosition(window.getSize().x / 2.f, window.getSize().y - 40);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		events(window);

		window.clear(sf::Color(33, 31, 48));

		window.draw(congratsText);
		window.draw(scoreText);
		window.draw(thanksText);
		window.draw(pressEnterText);

		window.display();
	}

}

int main() {
	sf::RenderWindow window;

	//window.create(sf::VideoMode(Final::rezolution, Final::rezolution), L"TheGame", sf::Style::Default);
	window.create(sf::VideoMode(Final::rezolution, Final::rezolution), L"TheGame", sf::Style::Default);

	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	sf::Image icon;
	icon.loadFromFile("images/icon.png");

	//text
	sf::Font font;
	font.loadFromFile("fonts/pixel.ttf");

	sf::Text newGameText;
	sf::Text exitText;
	sf::Text versionText;
	sf::Text controlsText;

	newGameText.setString("new game");
	newGameText.setFont(font);
	newGameText.setCharacterSize(24);
	newGameText.setColor(sf::Color::White);
	newGameText.setOrigin(newGameText.getLocalBounds().width / 2, newGameText.getLocalBounds().height / 2);
	newGameText.setPosition(window.getSize().x / 2, window.getSize().y - 80);

	exitText.setString("exit");
	exitText.setFont(font);
	exitText.setCharacterSize(24);
	exitText.setColor(sf::Color(100, 100, 100));
	exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
	exitText.setPosition(window.getSize().x / 2, window.getSize().y - 60);

	versionText.setString("v0.1 alpha");
	versionText.setFont(font);
	versionText.setCharacterSize(16);
	versionText.setColor(sf::Color::White);
	versionText.setPosition(window.getSize().x - 80, window.getSize().y - 20);

	controlsText.setString("A, D - move\nSpace - jump\nESC - pause\nR - restart");
	controlsText.setFont(font);
	controlsText.setCharacterSize(16);
	controlsText.setColor(sf::Color::White);
	controlsText.setPosition(0, 0);

	//

	//sounds
	sf::SoundBuffer soundBuffer;
	sf::Music music;

	soundBuffer.loadFromFile("sounds/switchMenu.ogg");
	sf::Sound sound(soundBuffer);
	sound.setVolume(20);

	music.openFromFile("sounds/mainMenuMusic.ogg");
	music.setVolume(50);
	music.play();
	music.setLoop(1);
	//

	int playerScore = 0;

	int menuSelector = 0;
	bool spam = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {
				//window->setPosition(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2));
				window.setSize(sf::Vector2u(600, 600));
			}

		}

		if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !spam) {
			newGameText.setColor(sf::Color::White);
			exitText.setColor(sf::Color(100, 100, 100));
			menuSelector = 0;

			sound.play();

			spam = true;
		}
		if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !spam) {
			newGameText.setColor(sf::Color(100, 100, 100));
			exitText.setColor(sf::Color::White);
			menuSelector = 1;

			sound.play();

			spam = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
			spam = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			switch (menuSelector)
			{
			case 0: {
				GameLauncher* gameLauncher = new GameLauncher(&window);

				music.stop();
				bool isFinish = gameLauncher->LaunchGame(playerScore);

				delete gameLauncher;


				window.setView(sf::View(sf::Vector2f(300, 300), sf::Vector2f(600, 600)));

				if (isFinish) {
					music.openFromFile("sounds/win.ogg");
					music.play();
					music.setLoop(0);

					drawCongratulationsWindow(window, playerScore);
				}

				music.openFromFile("sounds/mainMenuMusic.ogg");
				music.setLoop(1);
				music.play();

				menuSelector = -1;

				break;
			}
			case 1: {
				window.close();
				break;
			}

			}
		}

		window.clear(sf::Color(33, 31, 48));

		window.draw(newGameText);
		window.draw(exitText);
		window.draw(versionText);
		window.draw(controlsText);

		window.display();
	}


	return 0;
}