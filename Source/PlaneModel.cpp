#include "includes/PlaneModel.hpp"
#include <iostream>


PlaneModel::PlaneModel() {
    glm::vec3 color = glm::vec3(0.52f, 0.58f, 0.18f);
    
	//This plane appears slightly above other grid
	//When uv values are larger than one it gets tiled (in this case tiled 8 times in x direction and 8 times in z direction)
	Vertex planeGrid[] = {
		Vertex(glm::vec3(-25.f, 0.01, 25.0), color,glm::vec2(0.0f, 2.0f)),
		Vertex(glm::vec3(25.f, 0.01, 25.0), color,glm::vec2(2.0f, 2.0f)),
		Vertex(glm::vec3(25.f, 0.01, -25.0), color,glm::vec2(2.0f, 0.0f)),

		Vertex(glm::vec3(25.f, 0.01, -25.0), color,glm::vec2(2.0f, 0.0f)),
		Vertex(glm::vec3(-25.f, 0.01, -25.0), color,glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-25.f, 0.01, 25.0), color,glm::vec2(0.0f, 2.0f))
	};


	SimpleModel* plane = new SimpleModel(planeGrid, sizeof(planeGrid) / sizeof(glm::vec3), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
		glDrawArrays(GL_TRIANGLES, 0, 6);
		});
	
	this->addChild(plane);


	setupAttribPointer();
}