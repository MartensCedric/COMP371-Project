#include "includes/Model.hpp"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Model::Model() {}

Model::Model(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT))
{
	drawFunction = drawFunc;
	// Create a vertex array
	GLuint modelVAO;   //Create a VAO 
	glGenVertexArrays(1, &modelVAO); //Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(modelVAO);  //Tell openGL to use this VAO until I decide to change it (openGL is state machine)

	GLuint modelVBO;  //Create a VBO  (VBO's connect to a single VAO)
	glGenBuffers(1, &modelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec3), vertexArray, GL_STATIC_DRAW);

	vaoId = modelVAO;
	this->vertexCount = vertexCount;
}

void Model::setShader(int shaderProgram)
{
	shaderId = shaderProgram;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->shaderId = shaderProgram;
	}
};

void Model::draw()
{
	glUseProgram(shaderId);
	glBindVertexArray(vaoId);
	drawFunction(vertexCount, shaderId, this->getModelMatrix());

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw();
	}
}

void Model::scale(float x, float y, float z)
{
	this->objScaleMat = glm::scale(objScaleMat, glm::vec3(x, y, z));
}

void Model::rotate(float thetaX, float thetaY, float thetaZ)
{
	//Implement by modifying objRotMat
}

void Model::translate(float x, float y, float z)
{
	this->objTransMat = glm::translate(objTransMat, glm::vec3(x, y, z));
}

void Model::addChild(Model* child)
{
	child->parent = this;
	children.push_back(child);
}
\


glm::mat4 Model::getModelMatrix()
{
	if (this->parent == nullptr)
		return objTransMat * objRotMat * objScaleMat;

	glm::mat4 pRotMat = this->parent->objRotMat;
	glm::mat4 pScaleMat = this->parent->objScaleMat;
	glm::mat4 pTransMat = this->parent->objTransMat;

	return this->parent->getModelMatrix() * objTransMat * objRotMat * objScaleMat;

}
Model::~Model() {}