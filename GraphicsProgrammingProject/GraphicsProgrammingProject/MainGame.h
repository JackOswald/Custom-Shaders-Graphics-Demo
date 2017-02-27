#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h"

enum class GameState{ PLAY, EXIT };


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void processInputs();
	void gameLoop();
	void drawGame();

	GameDisplay _gameDisplay;
	GameState _gameState;
};

