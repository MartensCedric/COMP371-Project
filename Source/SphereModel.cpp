#include "includes/SphereModel.hpp"

SphereModel::SphereModel(float radius, int sectors, int stacks){
    float x, y, z, xy;                              // vertex position
    
    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    float sectorAngle, stackAngle;
    
    glm::vec3 color = glm::vec3(0.75f, 0.75f, 0.75f);
    std::vector<struct Vertex> v;
    for(int i = 0; i <= stacks; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;      // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            
            v.push_back(Vertex(glm::vec3(x, y, z), color, glm::vec2(0, 0)));
        }
    }

    // generate CCW index list of sphere triangles
    int k1, k2;
    for(int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);     // beginning of current stack
        k2 = k1 + sectors + 1;      // beginning of next stack

        for(int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                vertices.push_back(v.at(k1));
                //vertices.push_back(color);

                vertices.push_back(v.at(k2));
                //vertices.push_back(color);

                vertices.push_back(v.at(k1+1));
                //vertices.push_back(color);

                //indices.push_back(k1);
                //indices.push_back(k2);
                //indices.push_back(k1+1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stacks-1))
            {

                vertices.push_back(v.at(k1+1));
                //vertices.push_back(color);

                vertices.push_back(v.at(k2));
                //vertices.push_back(color);

                vertices.push_back(v.at(k2+1));
                //vertices.push_back(color);

                //indices.push_back(k1 + 1);
                //indices.push_back(k2);
                //indices.push_back(k2 + 1);
            }
        }
    }

    *this = SphereModel(
        &vertices[0], 
        vertices.size(), 
        [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
            GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }
    );

    setupAttribPointer();
}

SphereModel::SphereModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}
