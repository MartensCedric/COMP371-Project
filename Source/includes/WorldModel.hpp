#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "WaterModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"

class CloudModel : public SimpleModel {
	public:
		CloudModel();
};

class EModel : public SimpleModel {
	public: 
		EModel();
};

class FiveModel : public SimpleModel {
    public:
		FiveModel();
};

class IModel : public SimpleModel {
	public:
		IModel();
};

class ThreeModel : public SimpleModel {
	public:
		ThreeModel();
};

class TModel : public SimpleModel {
	public:
		TModel();
};

class DModel : public SimpleModel {
	public:
		DModel();
};

class EightModel : public SimpleModel {
	public:
		EightModel();
};

class WorldModel : public SimpleModel {
	public:
		std::vector<Model*> models;
		std::vector<Model*> spheres;
		std::vector<Model*> clouds;
		WorldModel();
		void setGridShader(int shaderProgram);
		void setAxesShader(int shaderProgram);
		void setModelShader(int shaderProgram);
		void setWaterShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		void setCloudsShader(int shaderProgram);
		void setTerrainShader(int shaderProgram);
		void generateForest();
		void generateClouds(GLuint TextureID);
		void addCloud(int elapsed_seconds, int modelShader);
		float getTerrainHeight(float x, float y);
		std::vector<Model*> texturedElement;
};