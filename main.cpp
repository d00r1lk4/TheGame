#include <SFML/Graphics.hpp>

#include "GameLauncher.h"

int main() {
	sf::RenderWindow window;

	window.create(sf::VideoMode(Final::rezolution, Final::rezolution), L"TheGame", sf::Style::Default);

	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	sf::Image icon;
	icon.loadFromFile("images/icon.png");

	//
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

	controlsText.setString("A, D - move\nSpace - jump\nESC - pause");
	controlsText.setFont(font);
	controlsText.setCharacterSize(16);
	controlsText.setColor(sf::Color::White);
	controlsText.setPosition(0, 0);

	//

	int menuSelector = 0;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			newGameText.setColor(sf::Color::White);
			exitText.setColor(sf::Color(100, 100, 100));
			menuSelector = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			newGameText.setColor(sf::Color(100, 100, 100));
			exitText.setColor(sf::Color::White);
			menuSelector = 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			switch (menuSelector)
			{
			case 0: {
				GameLauncher *gameLauncher = new GameLauncher(&window);
				gameLauncher->LaunchGame();
				delete gameLauncher;

				window.setView(sf::View(sf::Vector2f(300, 300), sf::Vector2f(600, 600)));

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