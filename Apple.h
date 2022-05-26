#pragma once

#include "Berries.h"

class Apple : public Berries {
private:

public:
	Apple(float x, float y);

	virtual bool update(float time);

	//virtual sf::String toString() { return "Apple"; }

};