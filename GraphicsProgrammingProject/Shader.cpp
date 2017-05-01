#include "Shader.h"
#include <iostream>
#include <fstream>


Shader::Shader(std::string res, std::string vert, std::string frag)
{
	currentProgram = glCreateProgram(); // Create our shader program

	currentShaders[0] = CreateShader(LoadShader(res + vert), GL_VERTEX_SHADER); // Create the vertex shader //"E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\shader.vert" C:\\Users\\JOSWAL200\\Desktop\\GraphicsProgrammingCoursework\\res\\shader.vert
	currentShaders[1] = CreateShader(LoadShader(res + frag), GL_FRAGMENT_SHADER); // Create the fragment shader //"E:\\Jack\\Documents\\Uni Work\\3rd Year\\Graphics Programming\\GraphicsProgrammingCoursework\\res\\shader.frag" C:\\Users\\JOSWAL200\\Desktop\\GraphicsProgrammingCoursework\\res\\shader.frag

	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(currentProgram, currentShaders[i]); // Adds all our shaders to the "currentShader"
	}

	glBindAttribLocation(currentProgram, 0, "position");
	glBindAttribLocation(currentProgram, 1, "textCoord");

	glLinkProgram(currentProgram); // Creates executables that will run on the GPU shaders
	ShaderErrorCheck(currentProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(currentProgram); // Checks the entire program is valid
	ShaderErrorCheck(currentProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(currentProgram, "transform");
}
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(currentProgram, currentShaders[i]); // Detach the shader from our program
		glDeleteShader(currentShaders[i]); // Delete the shaders from our program
	}
	glDeleteProgram(currentProgram); // Delete the program
}

void Shader::Bind()
{
	glUseProgram(currentProgram); //installs the program object specified by program as part of rendering state
}

void Shader::Update(const Transform& transform, const CameraHandler& camera) 
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	//glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::ShaderErrorCheck(GLuint currentShader, GLuint flag, bool program, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 }; 

	if (program)
	{
		glGetProgramiv(currentShader, flag, &success); 
	}
	else
	{
		glGetShaderiv(currentShader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (program)
		{
			glGetProgramInfoLog(currentShader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(currentShader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shaderProgram = glCreateShader(type);

	if (shaderProgram == 0) 
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; 
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shaderProgram, 1, stringSource, lengths); 
	glCompileShader(shaderProgram); 

	ShaderErrorCheck(shaderProgram, GL_COMPILE_STATUS, false, "Error compiling the shader");

	return shaderProgram;
}
 
