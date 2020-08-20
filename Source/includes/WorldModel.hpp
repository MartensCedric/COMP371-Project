#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "WaterModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"
#include "ConeModel.hpp"

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

class PenguinModel : public SimpleModel {
public:
	PenguinModel();
	void setBeakShader(int shaderID);

	ConeModel* beak;
};

class EightSnow : public SimpleModel {
public:
	EightSnow();
};


class WorldModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> spheres;
		std::vector<PenguinModel*> penguinos; // MEMES BY CEDRIC SMARTENS
		WorldModel();
		void setGridShader(int shaderProgram);
		void setAxesShader(int shaderProgram);
		void setModelShader(int shaderProgram);
		void setWaterShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		void setTerrainShader(int shaderProgram);
		//void setPenguinBeaksShader(int shaderProgram);
		void generateForest();
		void generatePenguins();
		float getTerrainHeight(float x, float y);
		std::vector<Model*> texturedElement;
};