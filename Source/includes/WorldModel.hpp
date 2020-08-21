#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "SphereModel.hpp"
#include "WaterModel.hpp"
#include "Terrain.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"
#include "ConeModel.hpp"

class PenguinModel : public SimpleModel {
public:
	PenguinModel();
	//void setBeakShader(int shaderID);

	ConeModel* beak;
};

struct Parameters;

class WorldModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> spheres;
		std::vector<PenguinModel*> penguinos; // MEMES BY CEDRIC SMARTENS

		WaterModel* plane = nullptr;
		Terrain* terrain = nullptr;

		Parameters parameters;

		WorldModel();
		void setModelShader(int shaderProgram);
		void setWaterShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		void setTerrainShader(int shaderProgram);
		void generateForest();
		void generatePenguins();
		void generateHouses();
		void generateStonehenge();
		float getTerrainHeight(float x, float y);
		void updateParameters();
		std::vector<Model*> texturedElement;
};
