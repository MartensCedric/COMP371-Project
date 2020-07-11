#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>

class UnitCubeModel : public SimpleModel {
    public:
        UnitCubeModel();
        UnitCubeModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
};