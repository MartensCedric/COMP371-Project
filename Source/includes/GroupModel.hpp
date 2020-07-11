#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,

class GroupModel : public Model
{
	public:
		GroupModel();
        void setupAttribPointer();
        void setShader(int shaderProgram);
        void draw();
		~GroupModel();
};