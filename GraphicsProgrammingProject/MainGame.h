#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "CameraHandler.h"

enum class GameState{ PLAY, EXIT };


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	GLfloat counter;

private:
	void initSystems();
	void processInputs();
	void gameLoop();
	void drawGame();

	GameDisplay _gameDisplay;
	GameState _gameState;
	Mesh mesh1;

	CameraHandler _gameCamera;


};

