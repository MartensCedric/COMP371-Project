#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "WaterModel.hpp"
#include "Terrain.hpp"
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

struct Parameters
{
	// To be honest, I don't see that much value in adding these caps to the GUI.
	int treeCap = 35;
	int penguinCap = 10;
	int cabinCap = 5;
	int	stonehengeCap = 1;

	int seed = 0xdeadbeef;

	float forestFrequency = 0.75; // [-1,1] Perhaps you can put it as [0,1] and then convert it to [-1,1]
	int forestDensity = 300; // 1: Always, 300 : Somewhat dense, 1000 : Sparse (This is the modulo value).
	
	float terrainHeight = 30.f;
	float waterHeight = 10.f;

	float penguinFrequency = 0.75f;
	int penguinDensity = 300;
};


class WorldModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> spheres;

		WaterModel* plane = nullptr;
		GridModel* grid = nullptr;
		AxesModel* axes = nullptr;
		Terrain* terrain = nullptr;

		Parameters parameters;

		WorldModel();
		void setAxesShader(int shaderProgram);
		void setModelShader(int shaderProgram);
		void setWaterShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		void setTerrainShader(int shaderProgram);
		void generateForest();
		void generateHouses();
		float getTerrainHeight(float x, float y);
		void updateParameters();
		std::vector<Model*> texturedElement;
};