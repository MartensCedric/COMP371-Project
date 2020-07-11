#pragma once
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <vector>

class Model
{
public:
	int vaoId;
	int shaderId;
	int vertexCount;
	glm::mat4 objScaleMat = glm::mat4(1.0f);
	glm::mat4 objTransMat = glm::mat4(1.0f);
	glm::mat4 objRotMat = glm::mat4(1.0f);
	void(*drawFunction)(int vertexCount, int shaderProgram, glm::mat4 objRBT) = [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {};
	std::vector<Model*> children;
	Model* parent = nullptr;

	Model();
	Model(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
	virtual void setupAttribPointer() = 0;
	void setShader(int shaderProgram);
	virtual void draw();
	void scale(float x, float y, float z);
	void rotate(float y, float x, float z, float angle);
	void translate(float x, float y, float z);
	void addChild(Model* child);
	glm::mat4 getModelMatrix();
	virtual ~Model();
};