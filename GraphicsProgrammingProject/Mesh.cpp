#include "Mesh.h"
#include <vector>


Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObj); // Delete our arrays
}

void Mesh::drawMesh()
{
	glBindVertexArray(vertexArrayObj);
	glDrawElements(GL_TRIANGLES, drawCounts, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::initMesh(Vertex* verts, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*verts[i].GetPosition());
		model.texCoords.push_back(*verts[i].GetTextCoord());
		model.normals.push_back(*verts[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	createModel(model);
}

void Mesh::loadModel(const std::string& fileName)
{
	IndexedModel modelToLoad = OBJModel(fileName).ToIndexedModel();
	createModel(modelToLoad);
}

void Mesh::createModel(const IndexedModel& model)
{
	drawCounts = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObj);
	glBindVertexArray(vertexArrayObj);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); 

	glBindVertexArray(0); 

}
