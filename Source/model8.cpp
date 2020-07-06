#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

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

	glVertexAttribPointer(
		0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	return modelVAO;
}