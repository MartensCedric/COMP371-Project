#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "PlaneModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"



class TreeTrunkModel : public SimpleModel {
public:
	TreeTrunkModel();
};

class RoundLeaves : public SimpleModel {
public:
	RoundLeaves();
};

class SquareLeaves : public SimpleModel {
public:
	SquareLeaves();
};

class CubeLeaves : public SimpleModel {
public:
	CubeLeaves();
};

class TreeModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		TreeModel();
		std::vector<Model*> texturedElement;
};

