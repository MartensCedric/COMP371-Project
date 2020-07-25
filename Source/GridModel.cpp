#include "includes/GridModel.hpp"

GridModel::GridModel() {
    glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.2f, 1);
	glm::vec3 normal = glm::vec3(0, 0, 0);
    
    std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-25, 0, 0), color, normal, glm::vec2(0, 1)),
		Vertex(glm::vec3(25, 0, 0), color, normal, glm::vec2(1, 0)),

		Vertex(glm::vec3(0, 0, -25), color, normal, glm::vec2(1, 1)),
		Vertex(glm::vec3(0, 0, 25), color, normal, glm::vec2(0, 0)),
	};

	for (int i = 0; i < 101; i++)
	{
		SimpleModel* xline = new SimpleModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, 2);
		});

		xline->translate(0, 0, -25.0f + i/2.0f);
		xline->setupAttribPointer();

		SimpleModel* zline = new SimpleModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 2, 2);
		});

		zline->translate(-25.0f + i/2.0f, 0, 0);
		zline->setupAttribPointer();

		this->addChild(xline);
		this->addChild(zline);
	}

	setupAttribPointer();
}