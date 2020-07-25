#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SimpleModel.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class SphereModel : public SimpleModel {
    public:
        std::vector<Vertex> vertices;
        
        // iniatiate the variable we are going to use
        float X1, Y1, X2, Y2, Z1, Z2;
        float inc1, inc2, inc3, inc4, inc5, radius1, radius2;

        // finally, create the buffers and bind the data to them
        std::vector<unsigned short> indices;
        std::vector<glm::vec3> indexed_vertices;

        SphereModel(float radius, int sectors, int stacks);
        SphereModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};