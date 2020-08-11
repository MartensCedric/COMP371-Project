#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>


class WaterModel : public SimpleModel {
    public:
        WaterModel();
		WaterModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};