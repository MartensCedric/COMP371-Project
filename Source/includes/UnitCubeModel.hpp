#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>
#include <vector>

class UnitCubeModel : public SimpleModel {
    public:
        UnitCubeModel();
        UnitCubeModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};