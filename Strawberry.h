#pragma once

#include "Berries.h"

class Strawberry : public Berries {
private:

public:
	Strawberry(float x, float y);

	virtual bool update(float time);

	//virtual sf::String toString() { return "Strawberry"; }

};