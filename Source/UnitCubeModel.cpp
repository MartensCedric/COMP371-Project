#include "includes/UnitCubeModel.hpp"


/**
* A subclass for an easy implementation of a 1x1x1 unit cube.
*/
UnitCubeModel::UnitCubeModel() {
    Vertex verticesUnitCube[] = {
        // Front face
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1),
        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1),
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1),

        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1),
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1),
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1),

        // Back face
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1),
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1),
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1),

        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1),
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1),
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1),

        // Left face
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1, 0, 0),
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1, 0, 0),
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1, 0, 0),

        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1, 0, 0),
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1, 0, 0),
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1, 0, 0),

        // Right face
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0),
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0),
        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0),

        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0),
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0),
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0),

        // Top face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0),
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0),
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0),

        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0),
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0),
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0),

        // Bottom face
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0),
        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0),
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0),

        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0),
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0),
    };

    
    *this = UnitCubeModel(
        verticesUnitCube, 
        sizeof(verticesUnitCube)/sizeof(glm::vec3), 
        [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {

			glm::vec3 spotlightPosition(0.0f, 5.0f, 6.0f);
			GLuint spotlightPositionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
			glUniform3fv(spotlightPositionLocation, 1, &spotlightPosition[0]);

			glm::vec3 ambientColor(1.0f, 0.843f, 0.0f);
			GLuint ambientColorLocation = glGetUniformLocation(shaderProgram, "ambientColor");
			glUniform3fv(ambientColorLocation, 1, &ambientColor[0]);

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

UnitCubeModel::UnitCubeModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: NormalsModel(vertexArray, vertexCount, drawFunc) 
{}
