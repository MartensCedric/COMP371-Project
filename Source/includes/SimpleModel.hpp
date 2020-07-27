#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,

class SimpleModel : public Model
{
	public:
		static std::vector<Model*> modelsBottom;
		static std::vector<Model*> modelsTop;
		
		SimpleModel();
		SimpleModel(glm::vec3 * vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
		SimpleModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
		virtual void setupAttribPointer() override;
		virtual ~SimpleModel();
};