#include "includes/GridModel.hpp"
#include <iostream>


GridModel::GridModel() {
    glm::vec3 color = glm::vec3(0.52f, 0.58f, 0.18f);
    
    Vertex verticesGridUnit[] = {
		Vertex(glm::vec3(-25.f, 0, 0), color,glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(25.0f, 0, 0), color,glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(0, 0, -25.f), color,glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0, 0, 25.f), color,glm::vec2(0.0f, 0.0f)),

	};
	//Set grid.setShader  to texture shader and uncomment these blocks of code for tiles texture on the ground

	////This plane appears slightly above other grid
	//Vertex planeGrid[] = {
	//	Vertex(glm::vec3(-25.f, 0.01, 25.0), color,glm::vec2(0.0f, 20.0f)),
	//	Vertex(glm::vec3(25.f, 0.01, 25.0), color,glm::vec2(20.0f, 20.0f)),
	//	Vertex(glm::vec3(25.f, 0.01, -25.0), color,glm::vec2(20.0f, 0.0f)),

	//	Vertex(glm::vec3(25.f, 0.01, -25.0), color,glm::vec2(20.0f, 0.0f)),
	//	Vertex(glm::vec3(-25.f, 0.01, -25.0), color,glm::vec2(0.0f, 0.0f)),
	//	Vertex(glm::vec3(-25.f, 0.01, 25.0), color,glm::vec2(0.0f, 20.0f))
	//};

	for (int i = 0; i < 101; i++)
	{
		SimpleModel* xline = new SimpleModel(verticesGridUnit, sizeof(verticesGridUnit) / sizeof(glm::vec3), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, 2);
		});

		xline->translate(0, 0, -25.0f + i/2.0f);
		xline->setupAttribPointer();

		SimpleModel* zline = new SimpleModel(verticesGridUnit, sizeof(verticesGridUnit) / sizeof(glm::vec3), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 2, 2);
		});

		zline->translate(-25.0f + i/2.0f, 0, 0);
		zline->setupAttribPointer();

		this->addChild(xline);
		this->addChild(zline);
	}

	//SimpleModel* plane = new SimpleModel(planeGrid, sizeof(planeGrid) / sizeof(glm::vec3), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
	//	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	//	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
	//	glDrawArrays(GL_TRIANGLES, 0, 6);
	//	});
	//this->addChild(plane);


	setupAttribPointer();
}