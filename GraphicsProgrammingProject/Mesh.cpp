#include "Mesh.h"


Mesh::Mesh(Vertex* verts, unsigned int numVertices)
{
	drawCounts = numVertices;
	glGenVertexArrays(1, &vertexArrayObj);
	glBindVertexArray(vertexArrayObj);
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(verts[0]), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObj); // Delete our arrays
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObj);
	glDrawArrays(GL_TRIANGLES, 0, drawCounts);
	glBindVertexArray(0);
}
