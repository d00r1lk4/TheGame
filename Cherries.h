#pragma once

#include "Berries.h"

class Cherries : public Berries {
private:

public:
	Cherries(float x, float y);

	virtual bool update(float time);

	//virtual sf::String toString() { return "Cherries"; }
};