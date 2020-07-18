#pragma once
#include "NormalsModel.h"
#include <glm/glm.hpp>

class UnitCubeModel : public NormalsModel {
    public:
        UnitCubeModel();
        UnitCubeModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
};