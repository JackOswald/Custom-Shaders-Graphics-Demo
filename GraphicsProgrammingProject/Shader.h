#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "CameraHandler.h"

class Shader
{
public:
	Shader(std::string res, std::string vert, std::string frag);
	~Shader();

	void Bind(); // Binds the shaders to our GPU
	void Update(const Transform& transform, const CameraHandler& camera);

	std::string Shader::LoadShader(const std::string& fileName);
	void Shader::ShaderErrorCheck(GLuint currentShader, GLuint flag, bool program, const std::string& errorMessage);
	GLuint Shader::CreateShader(const std::string& text, unsigned int type);
protected:
private:
	static const unsigned int NUM_SHADERS = 2; // The number of shaders
	
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint currentProgram; // Track the current shader program
	GLuint currentShaders[NUM_SHADERS]; // An array of our shaders
	GLuint uniforms[NUM_UNIFORMS]; // Number of uniform variables

};

