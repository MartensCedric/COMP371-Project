#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>

class UnitCubeModel : public SimpleModel {
    public:
        UnitCubeModel();
        UnitCubeModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};

