#include "MainGame.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();
}

void MainGame::processInputs()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) // get and process events
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInputs();
		drawGame();
	}
}

void MainGame::drawGame()
{
	
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);
	glEnd();

	_gameDisplay.swapBuffer();
}


