#pragma once

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
#define OS_Windows 0
#include "SimpleModel.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define OS_Windows 1
#include "../Source/includes/SimpleModel.hpp"
#endif


struct Parameters
{
	// Parameters for the GUI
	int seed = 0xdeadbeef;

	float forestFrequency = 0.75; // [-1,1] Perhaps you can put it as [0,1] and then convert it to [-1,1]
	int forestDensity = 24; // 1: Always, 300 : Somewhat dense, 1000 : Sparse (This is the modulo value).

	float terrainHeight = 10.0f;
	float waterHeight = -2.f;

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

class Terrain : public SimpleModel {
public:
	Terrain(Parameters* parameters);
	~Terrain();
	Terrain(Vertex* vertexArray, int vertexCount, float** heightmap, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
	static const int SIZE = 100;
	float** heightmap;
};

