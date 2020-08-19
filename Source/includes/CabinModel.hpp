#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"


class LogCabinBase : public SimpleModel {
public:
	LogCabinBase();
};


class CabinModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		CabinModel();
		std::vector<Model*> texturedElement;
};

