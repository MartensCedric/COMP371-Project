#pragma once

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#endif

#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader {
    public:
        static int light;
        static int texture;
        static int textureLight;
        static int passthrough;
        static int shadow;
        static int skybox;
        static int terrain;
        
        Shader();
        int compileShader(const char * path, int shaderType);
        int compileAndLinkShaders(const char * vertexPath, const char * fragmentPath);
};
