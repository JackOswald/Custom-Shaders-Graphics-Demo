#include "MainGame.h"
#include <iostream>
#include <string>

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
};

unsigned int indices[] = { 0, 1, 2 };
Transform _transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	GameDisplay* _gameDisplay = new GameDisplay(); // New game display
	CameraHandler* _gameCamera = new CameraHandler();
	Mesh* mesh();
	counter = 0;
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
	mesh1.loadModel("E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\monkey3.obj");
	_gameCamera.createCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
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
	
	_gameDisplay.clearDisplay(0.0f, 1.0f, 1.0f, 1.0f);

	//Shader shader(".\\res\\shader"); // New shader

	//_transform.SetPosition(glm::vec3(sinf(counter), 0.0, 0.0));
	//_transform.SetRotation(glm::vec3(0.0, 0.0, counter * 5));
	_transform.SetRotation(glm::vec3(0.0, 0.0, 0.0));
	//_transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
	Shader shader("E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\");
	Texture texture("E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\bricks.jpg");
	shader.Bind();
	shader.Update(_transform, _gameCamera);
	texture.Bind(0);
	mesh1.drawMesh();

	counter = counter + 0.01f;

	// old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}


