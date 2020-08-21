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
#include "ConeModel.hpp"

class CloudModel : public SimpleModel {
	public:
		CloudModel();
};

class PenguinModel : public SimpleModel {
public:
	PenguinModel();
	void setBeakShader(int shaderID);

	ConeModel* beak;
};

class WorldModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> spheres;
		std::vector<Model*> clouds;
		std::vector<PenguinModel*> penguinos; // MEMES BY CEDRIC SMARTENS

		WaterModel* plane = nullptr;
		GridModel* grid = nullptr;
		AxesModel* axes = nullptr;
		Terrain* terrain = nullptr;

		WorldModel();
		void setGridShader(int shaderProgram);
		void setAxesShader(int shaderProgram);
		void setModelShader(int shaderProgram);
		void setWaterShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		void setCloudsShader(int shaderProgram);
		void setTerrainShader(int shaderProgram);
		//void setPenguinBeaksShader(int shaderProgram);
		void generateForest();
		void generateClouds(GLuint TextureID);
		void generatePenguins();
		void generateHouses();
		void generateStonehenge();
		float getTerrainHeight(float x, float y);
		std::vector<Model*> texturedElement;
};