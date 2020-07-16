#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    public:
        GLfloat speed;
        glm::vec3 position;
        glm::vec3 lookAtPos;
        glm::vec3 up;
		GLfloat fov = 1.0f;

        Camera();
        void moveForward();
        void moveBack();
        void moveLeft();
        void moveRight();
		void setFOV(float fov);
		void setViewMatrix(int shader);
		void setProjectionMatrix(int shader);
		float getFOV();
};