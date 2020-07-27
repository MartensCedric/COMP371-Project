#include "includes/SimpleModel.hpp"

std::vector<Model*> SimpleModel::modelsBottom;
std::vector<Model*> SimpleModel::modelsTop;
		
SimpleModel::SimpleModel() {}

/**
* This subclass provides an easy implementation for models where the vertex attributes are pos+color.
*/
SimpleModel::SimpleModel(Vertex * vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: Model(vertexArray, vertexCount, drawFunc) {}

void SimpleModel::setupAttribPointer()
{
	// Position

	glVertexAttribPointer(
		0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		sizeof(Vertex),      // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);

	// Color

	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(glm::vec3)
	);
	glEnableVertexAttribArray(1);

	// Normal

	glVertexAttribPointer(
		2,                                              
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec4))
	);
	glEnableVertexAttribArray(2);

	// UV
	
	glVertexAttribPointer(
		3,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*) (2*sizeof(glm::vec3) + sizeof(glm::vec4))
	);
	glEnableVertexAttribArray(3);
}

SimpleModel::~SimpleModel() {}