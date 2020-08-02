#include "includes/Terrain.hpp"

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "../ThirdParty/FastNoise.h"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#include "../FastNoise.h"
#endif

std::vector<Vertex> getCubeVertices(float x, float y, float z) {
	glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1);
	return {
		// Front face
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 1.0f)),

		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 1.0f)), 

		// Back face
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 1.0f)), 

		// Left face
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 0.0f)),

		// Right face
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, -0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 1.0f)),

		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 1.0f)), 

		// Top face
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 1.0f)),

		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(x, y, z) + glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 0.0f)),
	};
}

Terrain::Terrain()
{
	FastNoise noise;
	noise.SetSeed(1337);
	noise.SetNoiseType(FastNoise::Simplex);

	std::vector<Vertex> vertices;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			std::vector<Vertex> v = getCubeVertices(i, noise.GetNoise(i*2, j*2) * 10.0f, j);
			vertices.insert(vertices.end(), v.begin(), v.end());
		}
	}

	*this = Terrain(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {

			glm::vec3 pointLightPosition(0.0f, 5.0f, 6.0f);
			GLuint pointlightPositionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
			glUniform3fv(pointlightPositionLocation, 1, &pointLightPosition[0]);

			glm::vec3 eyePosition = camera->position;
			GLuint eyePositionLocation = glGetUniformLocation(shaderProgram, "eyePosition");
			glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);
			
            GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);


			glm::mat4 lightProjection = glm::ortho(-25.f, 25.f, -25.f, 25.f,
				1.0f, 50.f);         // near and far (near > 0)
			glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f,30.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));

			glm::mat4 transformLightSpace = lightProjection * lightView;
			int transformLightSpaceLocation = glGetUniformLocation(shaderProgram, "transform_in_light_space");
			glUniformMatrix4fv(transformLightSpaceLocation, 1, GL_FALSE, &transformLightSpace[0][0]);
        
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
    );
    setupAttribPointer();
}

void Terrain::draw()
{
	glUseProgram(shaderId);
	int heightLoc = glGetUniformLocation(shaderId, "height");
	glUniform1f(heightLoc, height);

	Model::draw();
}

Terrain::Terrain(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}
