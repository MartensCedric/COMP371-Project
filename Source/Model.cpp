#include "Model.h"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

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
	this->objTransMat = glm::translate(objTransMat, glm::vec3(2, 3, 0));// Please remove when actually implementing rot, trans and scaling
}

void Model::setShader(int shaderProgram)
{
	shaderId = shaderProgram;
};

void Model::draw()
{
	glUseProgram(shaderId);
	glBindVertexArray(vaoId);
	drawFunction(vertexCount, shaderId, objTransMat * objRotMat);
}

void Model::scale(float scaleFactor)
{
	//Implement by modifying objRotMat
}

void Model::rotate(float thetaX, float thetaY, float thetaZ)
{
	//Implement by modifying objRotMat
}

void Model::translate(float x, float y, float z)
{
	//Implement by modifying objTransMat
}

Model::~Model()
{
}