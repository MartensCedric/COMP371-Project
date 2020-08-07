#pragma once

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
#define OS_Windows 0
#include "SimpleModel.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define OS_Windows 1
#include "../Source/includes/SimpleModel.hpp"
#endif

class Terrain : public SimpleModel {
public:
	Terrain();
	Terrain(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
	static const int SIZE = 100;
};

