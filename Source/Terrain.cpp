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
 
Terrain::Terrain(Parameters* parameters)
{
	FastNoise noise;
	noise.SetSeed((int)parameters->seed);
	noise.SetNoiseType(FastNoise::Simplex);

	std::vector<Vertex> vertices;
	float** tempHeightMap = new float*[SIZE];
	for (int i = 0; i < SIZE; i++)
		tempHeightMap[i] = new float[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			float height = noise.GetNoise(i * parameters->terrainSpread, j * parameters->terrainSpread) * parameters->terrainHeight;
			tempHeightMap[i][j] = height;
			std::vector<Vertex> v = getCubeVertices(i, height, j);
			vertices.insert(vertices.end(), v.begin(), v.end());
		}
	}

	*this = Terrain(&vertices[0], vertices.size(), tempHeightMap, [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {


			glm::vec3 eyePosition = camera->position;
			GLuint eyePositionLocation = glGetUniformLocation(shaderProgram, "eyePosition");
			glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);
			
            GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
        
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
    );
    setupAttribPointer();
}

Terrain::Terrain(Vertex* vertexArray, int vertexCount, float** heightmap, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera))
: SimpleModel(vertexArray, vertexCount, drawFunc), heightmap(heightmap)
{}

Terrain::~Terrain() {}