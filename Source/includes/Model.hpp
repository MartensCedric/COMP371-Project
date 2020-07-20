#pragma once
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <vector>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#include "Camera.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#include "../Source/includes/Camera.hpp"

#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Model
{
public:
	int vaoId;
	int shaderId;
	int vertexCount;
	glm::mat4 objScaleMat = glm::mat4(1.0f);
	glm::mat4 objTransMat = glm::mat4(1.0f);
	glm::mat4 objRotMat = glm::mat4(1.0f);
	void(*drawFunction)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) = [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {};
	std::vector<Model*> children;
	Model* parent = nullptr;
	Camera* camera = nullptr;

	Model();
	Model(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
	virtual void setupAttribPointer() = 0;
	virtual void setShader(int shaderProgram);
	virtual void setCamera(Camera* camera);
	virtual void draw();
	void scale(float x, float y, float z);
	void rotate(float y, float x, float z, float angle);
	void translate(float x, float y, float z);
	void addChild(Model* child);
	glm::mat4 getModelMatrix();
	void reset();
	virtual ~Model();
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};