#include "MainGame.h"
#include <iostream>
#include <string>

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
};

unsigned int indices[] = { 0, 1, 2 };
Transform transform1;
Transform transform2;
Transform transform3;

std::string RES_FOLDER = "E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\";

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	GameDisplay* _gameDisplay = new GameDisplay(); // New game display
	CameraHandler* _gameCamera = new CameraHandler(); // New camera handler
	Mesh* mesh();
	counter = 0.0f;
}

MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::mouseMovement()
{
	// Code taken and edited from: https://learnopengl.com/#!Getting-started/Camera (was also used in Games Programming 2 group project)
	
	// Calculate the time between frames to obtain deltaTime
	GLfloat currentFrame = SDL_GetTicks();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//std::cout << "Current frame = " << currentFrame << endl << "Current delta time = " << deltaTime << endl;

	//cameraSpeed = 2.0f * deltaTime;

	// Get current mouse position on the screen
	int xpos, ypos;
	SDL_GetGlobalMouseState(&xpos, &ypos);

	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sens = 0.50f;
	xOffset *= sens;
	yOffset *= sens;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	_gameCamera.forward = normalize(front);

	//SDL_WarpMouseInWindow(_gameDisplay._gameWindow, _gameDisplay.getWidth() / 2, _gameDisplay.getHeight() / 2);

	
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); // Initialise the game display

	SDL_WarpMouseInWindow(_gameDisplay._gameWindow, _gameDisplay.getWidth() / 2, _gameDisplay.getHeight() / 2);

	// Load the models
	model1.loadModel(RES_FOLDER + "Barrel_01.obj");
	model2.loadModel(RES_FOLDER + "stone.obj");
	model3.loadModel(RES_FOLDER + "crate.obj");

	// Set the models transforms attributes (position, scale, rotation)
	transform1.SetPosition(glm::vec3(2.0, 0.0, 0.0));
	transform1.SetScale(glm::vec3(0.50, 0.50, 0.50));
	transform1.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	transform2.SetPosition(glm::vec3(-2.0, 0.0, 0.0));
	transform2.SetScale(glm::vec3(0.60, 0.60, 0.60));
	transform2.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	transform3.SetPosition(glm::vec3(-0.6, 0.0, -0.5));
	transform3.SetScale(glm::vec3(0.65, 0.65, 0.65));
	transform3.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	_gameCamera.createCamera(glm::vec3(0.0f, 2.0f, 1.0f), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f); // Create the game camera
}


void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInputs();
		drawGame();
	}
}

void MainGame::processInputs()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) // Get and process events
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				mouseMovement();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_d:
						_gameCamera.MoveRight(1.0f);
						break;
	
					case SDLK_a:
						_gameCamera.MoveLeft(1.0f);
						break;

					case SDLK_w:
						_gameCamera.MoveUp(1.0f);
						break;

					case SDLK_s:
						_gameCamera.MoveDown(1.0f);
						break;

					case SDLK_q:
						_gameCamera.MoveForward(1.0f);
						break;

					case SDLK_e:
						_gameCamera.MoveBack(1.0f);
						break;

					case SDLK_ESCAPE:
						_gameState = GameState::EXIT;
						break;
					case SDLK_1:
						transform1.SetScale(glm::vec3(0.75, 0.75, 0.75));
						transform2.SetScale(glm::vec3(0.75, 0.75, 0.75));
						transform3.SetScale(glm::vec3(0.75, 0.75, 0.75));
						break;
					case SDLK_2:
						transform1.SetScale(glm::vec3(0.50, 0.50, 0.50));
						break;
					}
			default:
				break;
		}
	}
}


void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// Barrel model
	Shader shader(RES_FOLDER, "shader.vert", "shader.frag");
	Texture texture(RES_FOLDER + "barrel3.jpg");
	
	shader.Bind();
	shader.Update(transform1, _gameCamera);
	texture.Bind(0);
	model1.drawMesh();

	// Stone model
	Shader shader2(RES_FOLDER, "shader.vert", "shader.frag");
	Texture texture2(RES_FOLDER + "stone2.jpg");

	shader2.Bind();
	shader2.Update(transform2, _gameCamera);
	texture2.Bind(0);
	model2.drawMesh();

	// Crate model
	Shader shader3(RES_FOLDER, "shader.vert", "shader.frag");
	Texture texture3(RES_FOLDER + "crateTexture.jpg");

	shader3.Bind();
	shader3.Update(transform3, _gameCamera);
	texture3.Bind(0);
	model3.drawMesh();

	counter = counter + 0.01f;

	// Old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}


