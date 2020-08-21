#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"


class Stoneplate : public SimpleModel {
public:
	Stoneplate();
};

class EModel : public SimpleModel {
public:
	EModel();
};

class ESnow : public SimpleModel {
public:
	ESnow();
};

class FiveModel : public SimpleModel {
public:
	FiveModel();
};

class FiveSnow : public SimpleModel {
public:
	FiveSnow();
};

class IModel : public SimpleModel {
public:
	IModel();
};

class ISnow : public SimpleModel {
public:
	ISnow();
};

class ThreeModel : public SimpleModel {
public:
	ThreeModel();
};

class ThreeSnow : public SimpleModel {
public:
	ThreeSnow();
};

class TModel : public SimpleModel {
public:
	TModel();
};

class TSnow : public SimpleModel {
public:
	TSnow();
};

class DModel : public SimpleModel {
public:
	DModel();
};

class DSnow : public SimpleModel {
public:
	DSnow();
};

class EightModel : public SimpleModel {
public:
	EightModel();
};

class EightSnow : public SimpleModel {
public:
	EightSnow();
};


class StonehengeModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		StonehengeModel();
		~StonehengeModel();
		std::vector<Model*> texturedElement;
};

