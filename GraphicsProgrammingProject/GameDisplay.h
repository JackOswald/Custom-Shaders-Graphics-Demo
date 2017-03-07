#pragma once

#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>

using namespace std;

class GameDisplay
{
public:
	GameDisplay();
	~GameDisplay();
	void initDisplay();
	void swapBuffer();
	void ClearDisplay(float r, float g, float b, float a);

private:
	void returnError(std::string error);
	SDL_GLContext glContext; // Holds variable to hold the context
	SDL_Window* _gameWindow; // Holds the pointer to the game window
	int _screenWidth;
	int _screenHeight;
};

