#include "includes/NormalsModel.hpp"

NormalsModel::NormalsModel() {}

/**
* This subclass provides an easy implementation for models where the vertex attributes are pos+normal.
*/
NormalsModel::NormalsModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: Model::Model(vertices, verticesCount, indices, indicesCount, drawFunc)
{}

void NormalsModel::setupAttribPointer()
{
	glVertexAttribPointer(
		0,                     // attribute 0 matches aPos in Vertex Shader
		3,                     // size
		GL_FLOAT,              // type
		GL_FALSE,              // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0               // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,                            // attribute 1 matches aNormal in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // normal is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);
}

NormalsModel::~NormalsModel()
{}