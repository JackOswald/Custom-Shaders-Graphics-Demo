#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}
protected:
private:
	glm::vec3 pos;
};

class Mesh
{
public:
	Mesh(Vertex* verts, unsigned int numVertices);
	~Mesh();

	void draw();
protected:
private:
	enum
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint vertexArrayObj;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // Creates an array of buffers
	unsigned int drawCounts; // How much of the VAO we want to be drawn 

};

