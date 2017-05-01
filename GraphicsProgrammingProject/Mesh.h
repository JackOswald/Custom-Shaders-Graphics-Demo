#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, glm::vec2& textCoord, glm::vec3 normal)
	{
		this->pos = pos;
		this->textCoord = textCoord;
		this->normal = normal;
	}

	glm::vec3* GetPosition() { return &pos; }
	glm::vec2* GetTextCoord() { return &textCoord; }
	glm::vec3* GetNormal() { return &normal; }
protected:
private:
	glm::vec3 pos;
	glm::vec2 textCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void drawMesh();
	void initMesh(Vertex* verts, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& fileName);
	void createModel(const IndexedModel& model);
protected:
private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXTCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObj;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // Creates an array of buffers
	unsigned int drawCounts; // How much of the VAO we want to be drawn 

};

