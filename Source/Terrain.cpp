#include "includes/Terrain.hpp"

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "../ThirdParty/FastNoise.h"
#include "includes/TerrainCube.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#include "../FastNoise.h"
#include "../Source/includes/TerrainCube.hpp"
#endif


Terrain::Terrain()
{
	generate();
}

void Terrain::setupAttribPointer()
{
}

void Terrain::generate()
{
	children.clear(); // Should also delete pointers :) and free opengl stuff

	FastNoise noise;
	noise.SetSeed(1337);
	noise.SetNoiseType(FastNoise::Simplex);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			heightMap[i][j] = noise.GetNoise(i*2, j*2);
			TerrainCube* block = new TerrainCube();
			block->scale(1, 1, 5);
			block->height = heightMap[i][j];
			block->translate(i, heightMap[i][j] * 15.0f, j);
			addChild(block);
		}
	}
}

Terrain::~Terrain()
{
}
