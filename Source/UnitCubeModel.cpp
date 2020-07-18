#include "includes/UnitCubeModel.hpp"


/**
* A subclass for an easy implementation of a 1x1x1 unit cube.
*/
UnitCubeModel::UnitCubeModel() {
    glm::vec3 verticesUnitCube[] = {
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
        sizeof(verticesUnitCube)/sizeof(verticesUnitCube[0]), 
        [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {

            GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }
    );
    setupAttribPointer();
}

UnitCubeModel::UnitCubeModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT)) 
: NormalsModel(vertexArray, vertexCount, drawFunc) 
{}
