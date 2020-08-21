#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "WaterModel.hpp"
#include "Terrain.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"



struct Parameters
{
	// Parameters for the GUI
	int seed = 0xdeadbeef;

	float forestFrequency = 0.75; // [-1,1] Perhaps you can put it as [0,1] and then convert it to [-1,1]
	int forestDensity = 24; // 1: Always, 300 : Somewhat dense, 1000 : Sparse (This is the modulo value).
	
	float terrainHeight = 30.f;
	float waterHeight = 10.f;

	float penguinFrequency = 0.82f;
	int penguinDensity = 6;


	// To be honest, I don't see that much value in adding these caps to the GUI.
	int treeCap = 35;
	int penguinCap = 20;
	int cabinCap = 5;
	int	stonehengeCap = 1;

	//other parameters we might not want in the GUI
	//These multiple i,j values in the noise to skip values.
	int terrainSpread = 2;
	int penguinSpread = 3;
	int forestSpread = 1;
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
		void generateStonehenge();
		float getTerrainHeight(float x, float y);
		void updateParameters();
		std::vector<Model*> texturedElement;
};