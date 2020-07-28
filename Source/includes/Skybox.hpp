#pragma once

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
#define OS_Windows 0
#include "Model.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define OS_Windows 1
#include "../Source/includes/Model.hpp"
#endif


class Skybox : public Model
{
public:
	Skybox();
	virtual void setupAttribPointer() override;
	virtual void draw() override;
	virtual ~Skybox();
};

