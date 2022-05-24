#pragma once

#include <SFML/Graphics.hpp>

sf::View playerCamera;

sf::View setPlayerPosForCamera(float x, float y) {
	float tempX = x, tempY = y;

	if (x < 300) { tempX = 300; }	//left
	if (x > 420) { tempX = 420; }	//right
	if (y < 300) { tempY = 300; }	//up
	if (y > 300) { tempY = 300; }	//down

	playerCamera.setCenter(tempX, tempY - 136);
	return playerCamera;
}