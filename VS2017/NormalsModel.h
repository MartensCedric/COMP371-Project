#pragma once
#include "..\Source\includes\Model.hpp"
class NormalsModel :
	public Model
{
public:
	NormalsModel();
	NormalsModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
	virtual void setupAttribPointer() override;
	virtual ~NormalsModel();
};

