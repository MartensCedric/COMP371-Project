#pragma once
#include "../Source/includes/Model.hpp"
class Skybox : public Model
{
public:
	Skybox();
	virtual void setupAttribPointer() override;
	virtual void draw() override;
	virtual ~Skybox();
};

