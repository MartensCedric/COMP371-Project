#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

// We shouldn't have a function per model, but a few model files that are imported. 
// I created this function to have a template for the others to look one
// I'm keeping it in somewhat local coordinates so it's gonna be easy to change this code once we have 
// proper hierarchical modeling.
int create5VAO() // creates a VAO of the number 8
{
	// Upload geometry to GPU and return the Vertex Buffer Object ID

    glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 yellow = glm::vec3(1.0f , 1.0f, 0.0f);
    glm::vec3 cyan = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 pink = glm::vec3(1.0f, 0.0f, 1.0f);

	glm::vec3 vertexArray[] = {
	    // Position, Color        
		// Left top face
		glm::vec3(-1.0f, -0.25f, -1.0f), red,
		glm::vec3(-1.0f, 2.0f, 1.0f), red,
		glm::vec3(-1.0f, 2.0f, -1.0f), red,

		glm::vec3(-1.0f, -0.25f, -1.0f), red,
		glm::vec3(-1.0f, -0.25f, 1.0f), red,
		glm::vec3(-1.0f, 2.0f, 1.0f), red,

		// Left bottom face
		glm::vec3(-1.0f, -2.0f, -1.0f), red,
		glm::vec3(-1.0f, -1.5f, 1.0f), red,
		glm::vec3(-1.0f, -1.5f, -1.0f), red,

		glm::vec3(-1.0f, -2.0f, -1.0f), red,
		glm::vec3(-1.0f, -2.0f, 1.0f), red,
		glm::vec3(-1.0f, -1.5f, 1.0f), red,

		// Right top side
		glm::vec3(1.0f, 1.5f, -1.0f), red,
		glm::vec3(1.0f, 2.0f, -1.0f), red,
		glm::vec3(1.0f, 2.0f, 1.0f), red,

		glm::vec3(1.0f, 1.5f, -1.0f), red,
		glm::vec3(1.0f, 2.0f, 1.0f), red,
		glm::vec3(1.0f, 1.5f, 1.0f), red,

		// Right bottom side
		glm::vec3(1.0f, -2.0f, -1.0f), red,
		glm::vec3(1.0f, 0.25f, -1.0f), red,
		glm::vec3(1.0f, 0.25f, 1.0f), red,

		glm::vec3(1.0f, -2.0f, -1.0f), red,
		glm::vec3(1.0f, 0.25f, 1.0f), red,
		glm::vec3(1.0f, -2.0f, 1.0f), red,

		// Top side
		glm::vec3(-1.0f, 2.0f, -1.0f), red,
		glm::vec3(-1.0f, 2.0f, 1.0f), red,
		glm::vec3(1.0f, 2.0f, -1.0f), red,

		glm::vec3(-1.0f, 2.0f, 1.0f), red,
		glm::vec3(1.0f, 2.0f, 1.0f), red,
		glm::vec3(1.0f, 2.0f, -1.0f), red,

		// Bottom side
		glm::vec3(-1.0f, -2.0f, -1.0f), red,
		glm::vec3(1.0f, -2.0f, -1.0f), red,
		glm::vec3(-1.0f, -2.0f, 1.0f), red,

		glm::vec3(-1.0f, -2.0f, 1.0f), red,
		glm::vec3(1.0f, -2.0f, -1.0f), red,
		glm::vec3(1.0f, -2.0f, 1.0f), red,

		// Front face left
		glm::vec3(-1.0f, -0.25f, 1.0f), green,
		glm::vec3(-0.5f, 2.0f, 1.0f), green,
		glm::vec3(-1.0f, 2.0f, 1.0f), green,

		glm::vec3(-1.0f, -0.25f, 1.0f), green,
		glm::vec3(-0.5f, -0.25f, 1.0f), green,
		glm::vec3(-0.5f, 2.0f, 1.0f), green,

		// Front face right
		glm::vec3(0.5f, -2.0f, 1.0f), green,
		glm::vec3(1.0f, 0.25f, 1.0f), green,
		glm::vec3(0.5f, 0.25f, 1.0f), green,

		glm::vec3(0.5f, -2.0f, 1.0f), green,
		glm::vec3(1.0f, -2.0f, 1.0f), green,
		glm::vec3(1.0f, 0.25f, 1.0f), green,

		// Front face top
		glm::vec3(-0.5, 2.0f, 1.0f), green,
		glm::vec3(-0.5, 1.5f, 1.0f), green,
		glm::vec3(1, 2.0f, 1.0f), green,

		glm::vec3(-0.5, 1.5f, 1.0f), green,
		glm::vec3(1, 1.5f, 1.0f), green,
		glm::vec3(1, 2.0f, 1.0f), green,

		// Front face middle
		glm::vec3(-0.5f, 0.25f, 1.0f), green,
		glm::vec3(-0.5f, -0.25f, 1.0f), green,
		glm::vec3(0.5, 0.25f, 1.0f), green,

		glm::vec3(-0.5f, -0.25f, 1.0f), green,
		glm::vec3(0.5f, -0.25f, 1.0f), green,
		glm::vec3(0.5f, 0.25f, 1.0f), green,

		// Front face bottom
		glm::vec3(-1, -1.5f, 1.0f), green,
		glm::vec3(-1, -2.0f, 1.0f), green,
		glm::vec3(0.5, -1.5f, 1.0f), green,

		glm::vec3(-1, -2.0f, 1.0f), green,
		glm::vec3(0.5f, -2.0f, 1.0f), green,
		glm::vec3(0.5f, -1.5f, 1.0f), green,

		// Back face top
		glm::vec3(-0.5f, 2.0f, -1.0f), green,
		glm::vec3(0.5, 2.0f, -1.0f), green,
		glm::vec3(-0.5f, 1.5f, -1.0f), green,

		glm::vec3(-0.5f, 1.5f, -1.0f), green,
		glm::vec3(0.5f, 2.0f, -1.0f), green,
		glm::vec3(0.5f, 1.5f, -1.0f), green,

		// Back face middle
		glm::vec3(-0.5f, 0.5f, -1.0f), yellow,
		glm::vec3(0.5, 0.5f, -1.0f), yellow,
		glm::vec3(-0.5f, -0.5f, -1.0f), yellow,

		glm::vec3(-0.5f, -0.5f, -1.0f), yellow,
		glm::vec3(0.5f, 0.5f, -1.0f), yellow,
		glm::vec3(0.5f, -0.5f, -1.0f), yellow,

		// Back face bottom
		glm::vec3(-0.5f, -1.5f, -1.0f), yellow,
		glm::vec3(0.5, -1.5f, -1.0f), yellow,
		glm::vec3(-0.5f, -2.0f, -1.0f), yellow,

		glm::vec3(-0.5f, -2.0f, -1.0f), yellow,
		glm::vec3(0.5f, -1.5f, -1.0f), yellow,
		glm::vec3(0.5f, -2.0f, -1.0f), yellow,

		// Top hole left
		glm::vec3(-0.5f, 1.5f, 1.0f), red,
		glm::vec3(-0.5f, 0.25f, 1.0f), red,
		glm::vec3(-0.5, 1.5f, -1.0f), red,

		glm::vec3(-0.5f, 0.25f, 1.0f), red,
		glm::vec3(-0.5f, 0.25f, -1.0f), red,
		glm::vec3(-0.5, 1.5f, -1.0f), red,

		// Top hole top
		glm::vec3(-0.5f, 1.5f, -1.0f), pink,
		glm::vec3(0.5, 1.5f, -1.0f), pink,
		glm::vec3(-0.5f, 1.5f, 1.0f), pink,

		glm::vec3(-0.5, 1.5f, 1.0f), pink,
		glm::vec3(0.5, 1.5f, -1.0f), pink,
		glm::vec3(0.5, 1.5f, 1.0f), pink,

		// Top hole bottom
		glm::vec3(-0.5, 0.25f, -1.0f), pink,
		glm::vec3(-0.5, 0.25f, 1.0f), pink,
		glm::vec3(1, 0.25f, -1.0f), pink,

		glm::vec3(-0.5f, 0.25f, 1.0f), pink,
		glm::vec3(1, 0.25f, 1.0f), pink,
		glm::vec3(1, 0.25f, -1.0f), pink,

		// Bottom hole right
		glm::vec3(0.5f, -0.25f, 1.0f), red,
		glm::vec3(0.5, -0.25f, -1.0f), red,
		glm::vec3(0.5f, -1.5f, 1.0f), red,

		glm::vec3(0.5f, -1.5f, 1.0f), red,
		glm::vec3(0.5, -0.25f, -1.0f), red,
		glm::vec3(0.5f, -1.5f, -1.0f), red,

		// Bottom hole top
		glm::vec3(-0.5f, -0.5f, -1.0f), pink,
		glm::vec3(0.5, -0.5f, -1.0f), pink,
		glm::vec3(-0.5f, -0.5f, 1.0f), pink,

		glm::vec3(-0.5f, -0.5f, 1.0f), pink,
		glm::vec3(0.5, -0.5f, -1.0f), pink,
		glm::vec3(0.5f, -0.5f, 1.0f), pink,

		// Bottom hole bottom
		glm::vec3(-1, -1.5f, -1.0f), pink,
		glm::vec3(-1, -1.5f, 1.0f), pink,
		glm::vec3(0.5, -1.5f, -1.0f), pink,

		glm::vec3(-1, -1.5f, 1.0f), pink,
		glm::vec3(0.5f, -1.5f, 1.0f), pink,
		glm::vec3(0.5, -1.5f, -1.0f), pink,
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