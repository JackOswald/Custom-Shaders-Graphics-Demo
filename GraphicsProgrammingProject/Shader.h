#pragma once
#include <string>
#include <GL\glew.h>

class Shader
{
public:
	Shader(const std::string fileName);
	~Shader();

	void Bind(); // Binds the shaders to our GPU

	std::string LoadShader(const std::string& fileName);
	void ShaderErrorCheck(GLuint currentShader, GLuint flag, bool program, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
protected:
private:
	static const unsigned int NUM_SHADERS = 2; // The number of shaders
	Shader(const Shader& other){}
	void operator = (const Shader& other){}

	GLuint currentProgram; // Track the current shader program
	GLuint currentShaders[NUM_SHADERS]; // An array of our shaders

};

