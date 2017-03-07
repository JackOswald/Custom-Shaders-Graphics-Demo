#include "GameDisplay.h"


GameDisplay::GameDisplay()
{
	_gameWindow = nullptr; // Initialise to generate a null access violation for debugging;
	_screenWidth = 1024;
	_screenHeight = 768;
}

GameDisplay::~GameDisplay()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(_gameWindow);
	SDL_Quit();
}

void GameDisplay::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); // Initialise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Minimum number of biys used to display colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Set up double buffer

	_gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); // Create the window

	if (_gameWindow == nullptr)
	{
		returnError("Failed to create window");
	}

	glContext = SDL_GL_CreateContext(_gameWindow);

	if (glContext == nullptr)
	{
		returnError("Failed to create SDL_GL context");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void GameDisplay::swapBuffer()
{
	SDL_GL_SwapWindow(_gameWindow); // Swap our buffers
}

void GameDisplay::returnError(std::string error)
{
	std::cout << error << std::endl;
	std::cout << "Press any key to quit...";
	int input;
	std::cin >> input;
	SDL_Quit();
}

