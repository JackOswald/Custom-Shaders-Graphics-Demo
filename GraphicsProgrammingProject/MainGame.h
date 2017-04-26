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
	void MouseMovement();

	GLfloat counter;

private:
	void initSystems();
	void processInputs();
	void gameLoop();
	void drawGame();

	GLfloat deltaTime = 0.0f;
	GLfloat	lastFrame = 0.0f;
	GLfloat cameraSpeed = 0.0f;
	GLfloat	yaw = 20.0f;
	GLfloat pitch = 0.0f;
	GLfloat fov = glm::radians(45.0f);
	GLfloat lastX = 512;
	GLfloat lastY = 384;

	GameDisplay _gameDisplay;
	GameState _gameState;
	Mesh model1;
	Mesh model2;
	Mesh model3;

	CameraHandler _gameCamera;


};

