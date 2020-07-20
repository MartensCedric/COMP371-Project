#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,

class SimpleModel : public Model
{
	public:
		std::vector<glm::vec3> vertices;
        std::vector<unsigned short> indices;
		SimpleModel();
		SimpleModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
		virtual void setupAttribPointer() override;
		virtual ~SimpleModel();
};