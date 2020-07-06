#pragma once
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
class Model
{
protected:
	int vaoId;
	int vertexCount;
	int shaderId;
	void(*drawFunction)(int vertexCount, int shaderProgram);

public:
	Model(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram));
	virtual void setupAttribPointer() = 0;
	void setShader(int shaderProgram);
	virtual void draw();
	virtual ~Model();
};