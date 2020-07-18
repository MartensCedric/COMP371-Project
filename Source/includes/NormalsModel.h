#pragma once
#include "Model.hpp"
class NormalsModel :
	public Model
{
public:
	NormalsModel();
	NormalsModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera * camera));
	virtual void setupAttribPointer() override;
	virtual ~NormalsModel();
};
