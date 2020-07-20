#include "includes/Model.hpp"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Model::Model() {}


/**
* Model Class
* This is an OpenGL wrapper which allows you to create models with hierarchical modeling.
* The vertices must be specified as well as a routine that draws said model.
*/
Model::Model(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera))
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

/**
* Sets the camera that renders this model. Useful to get the view matrix
*/
void Model::setCamera(Camera* camera)
{
	this->camera = camera;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->setCamera(camera);
	}
}

/**
* Sets the shader for the model and its children
*/
void Model::setShader(int shaderProgram)
{
	shaderId = shaderProgram;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->setShader(shaderProgram);
	}
};

/**
* Draws the model. Binds the correct shader and VAO, it will also draw all the children.
*/
void Model::draw()
{
	glUseProgram(shaderId);
	glBindVertexArray(vaoId);
	this->camera->setProjectionMatrix(shaderId);
	this->camera->setViewMatrix(shaderId);
	drawFunction(vertexCount, shaderId, this->getModelMatrix(), this->camera);

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw();
	}
}

/**
* Scales the model
*/
void Model::scale(float x, float y, float z)
{
	this->objScaleMat = glm::scale(objScaleMat, glm::vec3(x, y, z));
}

/**
* Rotates the model
*/
void Model::rotate(float x, float y, float z, float angle)
{
	//Implement by modifying objRotMat
	float radianAngle = glm::radians(angle);
	glm::vec3 myRotationAxis(x, y, z);
	this->objRotMat = glm::rotate(objRotMat, radianAngle, myRotationAxis);
}

/**
* Translates the model
*/
void Model::translate(float x, float y, float z)
{
	this->objTransMat = glm::translate(objTransMat, glm::vec3(x, y, z));
}

/**
* Adds a child in the hierarchy for this model.
*/
void Model::addChild(Model* child)
{
	child->parent = this;
	children.push_back(child);
}


/**
* Gets the model matrix for this model.
* The model matrix is used to get the coordinate transform of this model in respect to the world.
* Children transformations are done first (at the right). The process is recursive.
*/
glm::mat4 Model::getModelMatrix()
{
	if (this->parent == nullptr)
		return objTransMat * objRotMat * objScaleMat;

	return this->parent->getModelMatrix() * objTransMat * objRotMat * objScaleMat;

}


/**
* Resets the orientation of the model.
*/
void Model::reset()
{
	this->objRotMat = glm::mat4(1);
	this->objTransMat = glm::mat4(1);
}

Model::~Model() {}