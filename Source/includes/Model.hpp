#pragma once
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
#include <vector>
#include "Camera.hpp"
#include "DirectionalLight.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Model
{
public:
	int vaoId;
	int shaderId;
	GLuint textureId;
	int vertexCount;
	bool isLetter;
	glm::mat4 objScaleMat = glm::mat4(1.0f);
	glm::mat4 objTransMat = glm::mat4(1.0f);
	glm::mat4 objRotMat = glm::mat4(1.0f);
	void(*drawFunction)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) = [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {};
	std::vector<Model*> children;
	Model* parent = nullptr;
	Camera* camera = nullptr;
	DirectionalLight* light = nullptr;
	int skybox = -1;
		
	Model();
	Model(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
	virtual void setupAttribPointer() = 0;
	virtual void setShader(int shaderProgram);
	virtual void setTexture(GLuint texture);
	virtual void setCamera(Camera* camera);
	virtual void setLight(DirectionalLight* light);
	virtual void setSkybox(int skybox);
	virtual void draw();
	void scale(float x, float y, float z);
	void rotate(float y, float x, float z, float angle);
	void translate(float x, float y, float z);
	void addChild(Model* child);
	glm::mat4 getModelMatrix() const;
	void reset();
	virtual ~Model();
};


struct Vertex
{
	Vertex(glm::vec3 _position, glm::vec4 _color, glm::vec3 _normal, glm::vec2 _uv)
		: position(_position), color(_color), normal(_normal), uv(_uv) {}

	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
};