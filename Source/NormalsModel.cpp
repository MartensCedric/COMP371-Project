#include "includes/NormalsModel.h"

NormalsModel::NormalsModel() {}

/**
* This subclass provides an easy implementation for models where the vertex attributes are pos+normal.
*/
NormalsModel::NormalsModel(Vertex * vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) : 
Model(vertexArray, vertexCount, drawFunc) {}

void NormalsModel::setupAttribPointer()
{
	glVertexAttribPointer(
		0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		sizeof(Vertex),      // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(
		1,                              // attribute 1 matches aNormal in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(glm::vec3)        // normal is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,                              // attribute 2 matches aUV in Vertex Shader
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(glm::vec3))  // uv is offseted by 2 vec3 (comes after position and color)
	);
	glEnableVertexAttribArray(2);
}

NormalsModel::~NormalsModel()
{}