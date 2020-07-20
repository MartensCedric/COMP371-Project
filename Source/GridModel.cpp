#include "includes/GridModel.hpp"

GridModel::GridModel() {
    glm::vec3 color = glm::vec3(0.52f, 0.58f, 0.18f);
    
    vertices = {
		glm::vec3(-25.f, 0, 0), color,
        glm::vec3(25.0f, 0, 0), color,

        glm::vec3(0, 0, -25.f), color,
        glm::vec3(0, 0, 25.f), color,
    };

	indices = {
		0, 1
	};

	for (int i = 0; i < 101; i++)
	{
		SimpleModel* xline = new SimpleModel(&vertices[0], 4, &indices[0], indices.size(), [](int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawElements(GL_LINES, indicesCount, GL_UNSIGNED_SHORT, 0);
		});

		xline->translate(0, 0, -25.0f + i/2.0f);
		xline->setupAttribPointer();

		SimpleModel* zline = new SimpleModel(&vertices[4], 4, &indices[0], indices.size(), [](int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawElements(GL_LINES, indicesCount, GL_UNSIGNED_SHORT, 0);
		});

		zline->translate(-25.0f + i/2.0f, 0, 0);
		zline->setupAttribPointer();

		this->addChild(xline);
		this->addChild(zline);
	}

	setupAttribPointer();
}