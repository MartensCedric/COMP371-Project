//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#include <iostream>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "SimpleModel.h"


glm::vec3 vertices8 [] = {

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




int compileShader(const char * path, int shaderType)
{
	std::ifstream file;
	file.open(path, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Failed to open shader : " << path << std::endl;
		return -1;
	}

	std::string contents;
	std::string line = "";
	while (!file.eof()) {
		std::getline(file, line);
		contents.append(line + "\n");
	}

	file.close();

	const char * source = contents.c_str();
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cerr << "Compilation failed for " << path << "\n" << infoLog << std::endl;
		return -1;
	}

	return shaderId;
}

int compileAndLinkShaders()
{
	// compile and link shader program
	 // return shader program id
	 // ------------------------------------

	 // vertex shader
	int vertexShader = compileShader("../Shaders/passthrough.vshader", GL_VERTEX_SHADER);

	if (vertexShader == -1)
		exit(EXIT_FAILURE);

	int fragmentShader = compileShader("../Shaders/passthrough.fshader", GL_FRAGMENT_SHADER);

	if (fragmentShader == -1)
		exit(EXIT_FAILURE);

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

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
    if (window == NULL)
    {
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

	// Camera parameters for view transform
	glm::vec3 cameraPosition(0.0f, 5.0f, 15.0f); //Where camera is positioned in 3d world
	glm::vec3 cameraLookAt(0.0f, 0.0f, -1.0f); //What position is the camera looking at in 3d world
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); //which direction is the top of the camera

	// Set projection matrix for the shader (in this case we use perspective projection)
	glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
												  1024.0f / 768.0f,  // aspect ratio
												  0.01f, 100.0f);   // near and far (near > 0)
	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    
	// Set the initial view matrix     					
	glm::mat4 viewMatrix = lookAt(cameraPosition,  // eye
								  cameraLookAt ,  // center
								  cameraUp); // up
	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	GLfloat cameraSpeed = 0.1f; //Set camera speed

    // Define and upload geometry to the GPU here ...
	SimpleModel modelGridCube(verticesGridCube, sizeof(verticesGridCube) / sizeof(verticesGridCube[0]), [](int vertexCount, int shaderProgram) {
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

	SimpleModel modelAxes(verticesAxes, sizeof(verticesAxes) / sizeof(verticesAxes[0]), [](int vertexCount, int shaderProgram) {
		glm::mat4 identity = glm::mat4(1.0f);
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glLineWidth(1);
	
	});

	modelAxes.setupAttribPointer();
	SimpleModel model8(vertices8, sizeof(vertices8)/sizeof(vertices8[0]), [](int vertexCount, int shaderProgram) {
		glm::mat4 identity = glm::mat4(1.0f);
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	});

	model8.setupAttribPointer();
	glEnable(GL_CULL_FACE); //With this enabled (surfaces with vertices in counter clockwise direction will render)
							//Therefore the back of a surface will not render (more efficient)

	glEnable(GL_DEPTH_TEST); //With this enabled, object behind other objects will not be rendered



    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window))
    {

        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


		 //Use shader program from compileAndLinkShaders()

		// Draw the 100x100 square grid on the ground
		modelGridCube.setShader(shaderProgram);
		modelGridCube.draw();

		modelAxes.setShader(shaderProgram);
		modelAxes.draw();


		model8.setShader(shaderProgram);
		model8.draw();

		
        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();

		//Handle Inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Terminate program
            glfwSetWindowShouldClose(window, true);
		

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //move forward
			cameraPosition += cameraSpeed * cameraLookAt;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //move back
			cameraPosition -= cameraSpeed * cameraLookAt;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //move left
			cameraPosition -= glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //move right
			cameraPosition += glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;


		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) //Switch to lines rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) //Switch to triangle rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) //Switch to points rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

		// Set initial view matrix again (because this is running in the "main while loop", it will update every frame)
		glm::mat4 viewMatrix = lookAt(cameraPosition, cameraLookAt+cameraPosition,  cameraUp); 
		GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
