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

// We shouldn't have a function per model, but a few model files that are imported. 
// I created this function to have a template for the others to look one
// I'm keeping it in somewhat local coordinates so it's gonna be easy to change this code once we have 
// proper hierarchical modeling.
int create8VAO() // creates a VAO of the number 8
{
	// Upload geometry to GPU and return the Vertex Buffer Object ID

	glm::vec3 vertexArray[] = {

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

	// Create a vertex array
	GLuint modelVAO;   //Create a VAO 
	glGenVertexArrays(1, &modelVAO); //Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(modelVAO);  //Tell openGL to use this VAO until I decide to change it (openGL is state machine)

	GLuint modelVBO;  //Create a VBO  (VBO's connect to a single VAO)
	glGenBuffers(1, &modelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);


	return modelVAO;
}


int createVertexArrayObject()
{
    // Upload geometry to GPU and return the Vertex Buffer Object ID

	glm::vec3 vertexArray[] = {
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

	// Create a vertex array
	GLuint vertexArrayObject;   //Create a VAO 
	glGenVertexArrays(1, &vertexArrayObject); //Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(vertexArrayObject);  //Tell openGL to use this VAO until I decide to change it (openGL is state machine)


	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;  //Create a VBO  (VBO's connect to a single VAO)
	glGenBuffers(1, &vertexBufferObject); 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);


	return vertexArrayObject;
}

int createAxesVAO()
{
	// Upload geometry to GPU and return the Vertex Buffer Object ID

	glm::vec3 vertexArray[] = {

		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f , 0.0f, 0.0f),
		glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f , 0.0f, 0.0f),

		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f , 1.0f, 0.0f),
		glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f , 1.0f, 0.0f),

		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f , 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f , 0.0f, 1.0f)
	};

	// Create a vertex array
	GLuint axesVAO;   //Create a VAO 
	glGenVertexArrays(1, &axesVAO); //Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(axesVAO);  //Tell openGL to use this VAO until I decide to change it (openGL is state machine)

	GLuint axesVBO;  //Create a VBO  (VBO's connect to a single VAO)
	glGenBuffers(1, &axesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, axesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);


	return axesVAO;
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
    int vao = createVertexArrayObject();
	int axesVAO = createAxesVAO();
	int model8VAO = create8VAO();

	glEnable(GL_CULL_FACE); //With this enabled (surfaces with vertices in counter clockwise direction will render)
							//Therefore the back of a surface will not render (more efficient)

	glEnable(GL_DEPTH_TEST); //With this enabled, object behind other objects will not be rendered



    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window))
    {

        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 



		glUseProgram(shaderProgram); //Use shader program from compileAndLinkShaders()
		glBindVertexArray(vao); //the type of data we are using and the vbo


		// Draw the 100x100 square grid on the ground
		for (int i = 0; i < 100; i++)
		{
			//draw rectangles in the x direction
			glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 0.5f));   //scale
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -25.0f + i * 0.5f));   //translate
			glm::mat4 worldMatrix = translationMatrix * scalingMatrix; //combine
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, 36); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

			//draw rectangles in the z direction
			glm::mat4 scalingMatrix1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 50.0f));   //scale
			glm::mat4 translationMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f + i * 0.5f, 0.0f, -0.25f));   //translate
			glm::mat4 worldMatrix1 = translationMatrix1 * scalingMatrix1; //combine
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix1[0][0]); //send worldMatrix1 data to that memory location
			glDrawArrays(GL_LINES, 0, 36); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

		}


		glBindVertexArray(axesVAO);
		glm::mat4 identity = glm::mat4(1.0f);
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, 6);
		glLineWidth(1);

		glBindVertexArray(model8VAO);
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 120);
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
