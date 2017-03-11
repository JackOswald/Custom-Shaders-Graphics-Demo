#include "MainGame.h"
#include <iostream>
#include <string>

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	GameDisplay* _gameDisplay = new GameDisplay(); // New game display
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

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
		Vertex(glm::vec3(0, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //size calcuated by number of bytes of an array / no bytes of one element
	Shader shader(".\\res\\shader"); //new shader
	shader.Bind();
	mesh.Draw();

	// old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}


