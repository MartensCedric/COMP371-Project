#pragma once
#include "Model.h"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs


class SimpleModel :
	public Model
{
	public:
		SimpleModel(glm::vec3* vertexArray, void(*drawFunc)(int vertexCount));
		virtual void setupAttribPointer() override;
		virtual ~SimpleModel();
};