#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

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

	glVertexAttribPointer(
		0,                   // attribute 0 matches aPos in Vertex Shader
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