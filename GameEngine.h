#pragma once

#include "AudioRenderingEngine.h"
#include "GraphicsRenderingEngine.h"
#include "PhysicsEngine.h"

class GameEngine {
private:
	GameEngine() {}

public:
	static AudioRenderingEngine AudioRender;
	static GraphicsRenderingEngine GraphicsRender;
	static PhysicsEngine Physics;


};

AudioRenderingEngine GameEngine::AudioRender;
GraphicsRenderingEngine GameEngine::GraphicsRender;
PhysicsEngine GameEngine::Physics;