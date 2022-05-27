#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class AudioRenderingEngine {
private:
	sf::SoundBuffer soundBuffer;

	sf::Music music;
	sf::Sound sound;

public:
	AudioRenderingEngine() {
		
	}

	void PlayMusic(sf::String path) {
		music.openFromFile(path);

		music.play();
		music.setLoop(1);
	}

	void PlaySound(sf::String path) {
		soundBuffer.loadFromFile(path);
		sound.setBuffer(soundBuffer);

		std::cout << "play";

		sound.play();
	}

};