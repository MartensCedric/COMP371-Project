#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"


class LogCabinBase : public SimpleModel {
public:
	LogCabinBase();
};


class CabinModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> texturedElement;
		CabinModel();
		~CabinModel();
};

