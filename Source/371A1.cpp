//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "includes/shader.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/shader.hpp"

#include "../Source/includes/shader.hpp"
#endif

#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "SimpleModel.h"
#include "camera.cpp"

glm::vec3 verticesUnitCube[] = {
	// Front face
	glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	// Back face
	glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	// Left face
	glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	// Right face
	glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	// Top face
	glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	// Bottom face
	glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),

	glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
	glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.75f, 0.75f, 0.75f),
};

glm::vec3 vertices3[] = {

	// Position, Color

	// Left face
	glm::vec3(-1.0f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	//Left face bottom
	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	//left face middle
	glm::vec3(-0.5f, -0.25f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.5f, 0.25f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.5f, 0.25f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.5f, -0.25f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.5f, -0.25f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.5f, 0.25f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Right side
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Top side
	glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Bottom side
	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Front face right
	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face top
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-1.0f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-1.0f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face middle
	glm::vec3(-0.5f, 0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 0.25f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face bottom
	glm::vec3(-1.0f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face top
	glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-1.0f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-1.0f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face left
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

	glm::vec3(0.5f, -2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

	// Back face middle
	glm::vec3(-0.5f, 0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -0.25f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face bottom
	glm::vec3(-1.0f, -1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.5f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Top hole right
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, 0.25f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(0.5f, 0.25f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, 0.25f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	// Top hole top
	glm::vec3(-1.0f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-1.0f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-1.0f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// Top hole bottom
	glm::vec3(-0.5f, 0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, 0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, 0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// Bottom hole right
	glm::vec3(0.5f, -0.25f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, -0.25f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, -0.25f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	// Bottom hole top
	glm::vec3(-0.5f, -0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, -0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, -0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -0.25f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, -0.25f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// Bottom hole bottom
	glm::vec3(-1.0f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-1.0f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-1.0f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
};

glm::vec3 vertices8[] = {

	// Position, Color

	// Left face
	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Right side
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Top side
	glm::vec3(-1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Bottom side
	glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Front face left
	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face right
	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face top
	glm::vec3(-0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face middle
	glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face bottom
	glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face top
	glm::vec3(-0.5f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face middle
	glm::vec3(-0.5f, 0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(0.5, 0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(-0.5f, -0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, 0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -0.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),

	// Back face bottom
	glm::vec3(-0.5f, -1.5f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(-0.5f, -2.0f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),

	glm::vec3(-0.5f, -2.0f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),
	glm::vec3(0.5f, -1.5f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(0.5f, -2.0f, -1.0f), glm::vec3(1.0f , 1.0f, 0.0f),

	// Top hole left
	glm::vec3(-0.5f, 1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5f, 0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	// Top hole right
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),


	// Top hole top
	glm::vec3(-0.5f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// Top hole bottom
	glm::vec3(-0.5f, 0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, 0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),


	// Bottom hole left
	glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(-0.5, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	// Bottom hole right
	glm::vec3(0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),


	// Bottom hole top
	glm::vec3(-0.5f, -0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -0.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, -0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// Bottom hole bottom
	glm::vec3(-0.5f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.5, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
};

glm::vec3 verticesI[] = {

	// Position, Color

	// Left side top
	glm::vec3(-0.75f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.75f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, 1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	//Left side bottom
	glm::vec3(-0.75f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, -1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, -1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.75f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, -1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	//left side middle
	glm::vec3(-0.25f, -1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.25f, -1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.25f, -1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	//Right side top
	glm::vec3(0.75f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(0.75f, 1.5f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 1.5f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Top side
	glm::vec3(-0.75f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Bottom side
	glm::vec3(-0.75f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(-0.75f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(-0.75f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, -1.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, 1.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	// Front face right
	glm::vec3(-0.25f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.25f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.25f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.25f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.25f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face top
	glm::vec3(-0.75f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.75f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.75f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, 1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Front face bottom
	glm::vec3(-0.75f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.75f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.75f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, -1.5f, 1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face top
	glm::vec3(-0.75f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(-0.75f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.75f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, 2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, 1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// Back face middle
	glm::vec3(0.25f, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.25f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

	glm::vec3(-0.25f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-0.25f, 1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.25f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

	// Back face bottom
	glm::vec3(-0.75f, -1.5f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-0.75f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(-0.75f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, -1.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	// right side middle
	glm::vec3(0.25f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.25f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.25f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

	glm::vec3(0.25f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.25f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.25f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

	// Top hole top
	glm::vec3(-0.75f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.75f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.75f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75f, 1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75f, 1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	// right side bottom
	glm::vec3(0.75f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

	glm::vec3(0.75f, -2.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.75f, -2.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

	// Bottom hole bottom
	glm::vec3(-0.75f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-0.75f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(-0.75f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75f, -1.5f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.75f, -1.5f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
};

glm::vec3 verticesGridCube[] = {
	// Cube model

	// position,                            color

	//left side
	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	// back side
	glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

	glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	// bottom side
	glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.2f, 0.29f, 0.29f),
	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.2f, 0.29f, 0.29f),// this color corresponds to diagonal line in the rectangle
	glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.2f, 0.29f, 0.29f),

	glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	// front side
	glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),

	glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	// right side
	glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),

	glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	// top side
	glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

	glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
	glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f)

};

glm::vec3 verticesAxes[] = {

	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f , 0.0f, 0.0f),
	glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f , 0.0f, 0.0f),

	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f , 1.0f, 0.0f),
	glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f , 1.0f, 0.0f),

	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f , 0.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f , 0.0f, 1.0f)
};

int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // greyish background color
    glClearColor(0.2f, 0.29f, 0.29f, 1.0f);

    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders();
	glUseProgram(shaderProgram);

	//----------Camera setup----------
	Camera camera = Camera(shaderProgram);

	// Set the initial view matrix     					
	camera.update();

	GLfloat cameraSpeed = 0.1f; //Set camera speed

    // Define and upload geometry to the GPU here ...

	SimpleModel modelGridCube(verticesGridCube, sizeof(verticesGridCube) / sizeof(verticesGridCube[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		for (int i = 0; i < 100; i++)
		{
			//draw rectangles in the x direction
			glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 0.5f));   //scale
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -25.0f + i * 0.5f));   //translate
			glm::mat4 worldMatrix = translationMatrix * scalingMatrix; //combine
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, vertexCount); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

			//draw rectangles in the z direction
			glm::mat4 scalingMatrix1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 50.0f));   //scale
			glm::mat4 translationMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f + i * 0.5f, 0.0f, -0.25f));   //translate
			glm::mat4 worldMatrix1 = translationMatrix1 * scalingMatrix1; //combine
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix1[0][0]); //send worldMatrix1 data to that memory location
			glDrawArrays(GL_LINES, 0, vertexCount); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

		}	
	});

	modelGridCube.setupAttribPointer();

	SimpleModel modelAxes(verticesAxes, sizeof(verticesAxes) / sizeof(verticesAxes[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		glm::mat4 identity = glm::mat4(1.0f); //use objRBT once the Rot,Trans,Scale has been implemented
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glLineWidth(1);
	
	});

	modelAxes.setupAttribPointer();
	SimpleModel modelUnitCube(verticesUnitCube, sizeof(verticesUnitCube)/sizeof(verticesUnitCube[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	});

	modelUnitCube.setupAttribPointer();
	glEnable(GL_CULL_FACE); //With this enabled (surfaces with vertices in counter clockwise direction will render)
							//Therefore the back of a surface will not render (more efficient)

	glEnable(GL_DEPTH_TEST); //With this enabled, object behind other objects will not be rendered

	float panInitCurPosX = -1;
	bool isPanning = true;
	glm::vec3 panInitialLookAt = glm::vec3(1.0f);

    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {
        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		double xCursorPos;
		double yCursorPos;
		glfwGetCursorPos(window, &xCursorPos, &yCursorPos);

	    //Use shader program from compileAndLinkShaders()

		// Draw the 100x100 square grid on the ground
		modelGridCube.setShader(shaderProgram);
		modelGridCube.draw();

		modelAxes.setShader(shaderProgram);
		modelAxes.draw();


		modelUnitCube.setShader(shaderProgram);
		modelUnitCube.draw();

        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();

		//Handle Inputs

		//Terminate program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
		
		//move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
			//cameraPosition += cameraSpeed * cameraLookAt;
			modelUnitCube.translate(0, 0, -1);

		//move back
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
			//cameraPosition -= cameraSpeed * cameraLookAt;
			modelUnitCube.translate(0, 0, 1);

		//move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
			//cameraPosition -= glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;
			modelUnitCube.translate(-1, 0, 0);

		//move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
			//cameraPosition += glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;
			modelUnitCube.translate(1, 0, 0);

		//Switch to lines rendering mode
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Switch to triangle rendering mode
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Switch to points rendering mode
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

		// Scale Up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
			modelUnitCube.scale(1.05);
		
		// Scale Down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
			modelUnitCube.scale(0.95);

		// Pan X
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (!isPanning)
			{
				panInitCurPosX = xCursorPos;
				isPanning = true;
				panInitialLookAt = camera.lookAtPos - camera.position;
			}
			else {
				glm::mat4 panMat(1.0f);

				std::cout << (xCursorPos - panInitCurPosX) / 3.0f << std::endl;
				glm::rotate(panMat, (float) 45.0f, glm::vec3(0.0, 0.0, 1.0));
				camera.lookAtPos = glm::vec3(panMat * glm::vec4(panInitialLookAt, 1.0f)) + camera.position;
			}
		}

		// Pan X
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			isPanning = false;
			panInitCurPosX = -1;
			panInitialLookAt = glm::vec3(1.0f);
		}

		// Tilt Y
		if (glfwGetKey(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{

		}

		// Tilt Y
		if (glfwGetKey(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
		{

		}


		// Set initial view matrix again (because this is running in the "main while loop", it will update every frame)
		camera.update();
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
