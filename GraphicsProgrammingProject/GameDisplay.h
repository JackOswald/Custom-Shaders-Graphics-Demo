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
	void clearDisplay(float r, float g, float b, float a);

	float getHeight();
	float getWidth();

	SDL_Window* _gameWindow; // Holds the pointer to the game window

private:
	void returnError(std::string error);

	SDL_GLContext glContext; // Holds global variable for the context

	float _screenWidth;
	float _screenHeight;
};

