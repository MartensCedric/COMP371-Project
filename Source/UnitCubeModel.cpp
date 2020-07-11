#include "includes/UnitCubeModel.hpp"

UnitCubeModel::UnitCubeModel() {
    glm::vec3 color = glm::vec3(0.75f, 0.75f, 0.75f);
    glm::vec3 verticesUnitCube[] = {
        // Front face
        glm::vec3(-1.0f, -1.0f, 1.0f), color,
        glm::vec3(1.0f, -1.0f, 1.0f), color,
        glm::vec3(1.0f, 1.0f, 1.0f), color,

        glm::vec3(-1.0f, -1.0f, 1.0f), color,
        glm::vec3(1.0f, 1.0f, 1.0f), color,
        glm::vec3(-1.0f, 1.0f, 1.0f), color,

        // Back face
        glm::vec3(-1.0f, -1.0f, -1.0f), color,
        glm::vec3(1.0f, 1.0f, -1.0f), color,
        glm::vec3(1.0f, -1.0f, -1.0f), color,

        glm::vec3(-1.0f, -1.0f, -1.0f), color,
        glm::vec3(-1.0f, 1.0f, -1.0f), color,
        glm::vec3(1.0f, 1.0f, -1.0f), color,

        // Left face
        glm::vec3(-1.0f, -1.0f, -1.0f), color,
        glm::vec3(-1.0f, -1.0f, 1.0f), color,
        glm::vec3(-1.0f, 1.0f, -1.0f), color,

        glm::vec3(-1.0f, -1.0f, 1.0f), color,
        glm::vec3(-1.0f, 1.0f, 1.0f), color,
        glm::vec3(-1.0f, 1.0f, -1.0f), color,

        // Right face
        glm::vec3(1.0f, -1.0f, -1.0f), color,
        glm::vec3(1.0f, 1.0f, -1.0f), color,
        glm::vec3(1.0f, -1.0f, 1.0f), color,

        glm::vec3(1.0f, -1.0f, 1.0f), color,
        glm::vec3(1.0f, 1.0f, -1.0f), color,
        glm::vec3(1.0f, 1.0f, 1.0f), color,

        // Top face
        glm::vec3(-1.0f, 1.0f, -1.0f), color,
        glm::vec3(-1.0f, 1.0f, 1.0f), color,
        glm::vec3(1.0f, 1.0f, 1.0f), color,

        glm::vec3(1.0f, 1.0f, 1.0f), color,
        glm::vec3(1.0f, 1.0f, -1.0f), color,
        glm::vec3(-1.0f, 1.0f, -1.0f), color,

        // Bottom face
        glm::vec3(-1.0f, -1.0f, -1.0f), color,
        glm::vec3(1.0f, -1.0f, 1.0f), color,
        glm::vec3(-1.0f, -1.0f, 1.0f), color,

        glm::vec3(1.0f, -1.0f, 1.0f), color,
        glm::vec3(-1.0f, -1.0f, -1.0f), color,
        glm::vec3(1.0f, -1.0f, -1.0f), color,
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
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}
