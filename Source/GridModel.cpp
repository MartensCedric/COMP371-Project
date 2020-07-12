#include "includes/GridModel.hpp"
#include <iostream>

GridModel::GridModel() {
    glm::vec3 color = glm::vec3(0.52f, 0.58f, 0.18f);
    
    glm::vec3 verticesGridUnit[] = {
		glm::vec3(-50.0f, 0, 0), color,
        glm::vec3(50.0f, 0, 0), color,

        glm::vec3(0, 0, -50.0f), color,
        glm::vec3(0, 0, 50.0f), color,
    };

	for (int i = 0; i < 100; i++)
	{
		SimpleModel* xline = new SimpleModel(verticesGridUnit, sizeof(verticesGridUnit) / sizeof(verticesGridUnit[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, 2);
		});

		xline->translate(0, 0, -50.0f + i);
		xline->setupAttribPointer();

		SimpleModel* zline = new SimpleModel(verticesGridUnit, sizeof(verticesGridUnit) / sizeof(verticesGridUnit[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 2, 2);
		});

		zline->translate(-50.0f + i, 0, 0);
		zline->setupAttribPointer();

		this->addChild(xline);
		this->addChild(zline);
	}

	setupAttribPointer();
}

void GridModel::setShader(int shaderProgram)
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->setShader(shaderProgram);
	}
}