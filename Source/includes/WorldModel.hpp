#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include "GridModel.hpp"
#include "AxesModel.hpp"
#include "SphereModel.hpp"
#include "PlaneModel.hpp"
#include "Shader.hpp"
#include "LoadTexture.hpp"

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
		WorldModel();
		void setModelShader(int shaderProgram);
		void setSphereShader(int shaderProgram);
		std::vector<Model*> texturedElement;
};