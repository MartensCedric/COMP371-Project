#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include <glm/glm.hpp>

/**
* A cone class :)
*/
class ConeModel : public SimpleModel {
public:
	ConeModel(glm::vec4 color);
	ConeModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
	virtual void setupAttribPointer() override;
	virtual ~ConeModel() {};
};