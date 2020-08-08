#include "includes/ConeModel.hpp"
#include "includes/UnitCubeModel.hpp"

/**
* A class for the implementation of a cone
*/
ConeModel::ConeModel(glm::vec4 color) : SimpleModel::SimpleModel() {
	float radius = 1;
	float height = 1.0f;
	std::vector<Vertex> bottom_vertices;
	std::vector<Vertex> top_vertices;

	bottom_vertices.push_back(Vertex(glm::vec3(0, 0, 0), color, glm::vec2(0, 0)));
	top_vertices.push_back(Vertex(glm::vec3(0, height, 0), color, glm::vec2(0, 0)));

	int fan_count = 25;
	for (int i = 0; i <= fan_count; i++)
	{
		float theta = i * 2.0f * M_PI / (float)fan_count;
		bottom_vertices.push_back(Vertex(glm::vec3(radius*cos(theta), 0, radius*sin(theta)), color, glm::vec2(cos(theta), sin(theta))));
		top_vertices.push_back(Vertex(glm::vec3(radius*cos(theta), 0, radius*sin(-theta)), color, glm::vec2(cos(theta), sin(theta))));
	}

	std::vector<Vertex> vertices = top_vertices;
	vertices.insert(vertices.end(), bottom_vertices.begin(), bottom_vertices.end());
	this->vertexCount = top_vertices.size() + bottom_vertices.size();

	*this = ConeModel(&vertices[0],
		vertices.size(),
		[](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {

		glm::vec3 eyePosition = camera->position;
		GLuint eyePositionLocation = glGetUniformLocation(shaderProgram, "eyePosition");
		glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);

		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);

		int topVertices = vertexCount / 2;
		int bottomVertices = topVertices;
		glDrawArrays(GL_TRIANGLE_FAN, 0, topVertices);
		glDrawArrays(GL_TRIANGLE_FAN, topVertices, bottomVertices);
	}
	);
	setupAttribPointer();
}

void ConeModel::setupAttribPointer()
{
	// Position

	glVertexAttribPointer(
		0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		sizeof(Vertex),      // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);

	// Color

	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(glm::vec3)
	);
	glEnableVertexAttribArray(1);


	// UV

	glVertexAttribPointer(
		3,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec4))
	);
	glEnableVertexAttribArray(2);
}


ConeModel::ConeModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera))
	: SimpleModel(vertexArray, vertexCount, drawFunc)
{}
