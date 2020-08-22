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
		GLfloat fov = 0.75f;
        int width;
        int height;

        Camera(int width, int height);
        ~Camera();
        void moveForward();
        void moveBack();
        void moveLeft();
        void moveRight();
		void setFOV(float fov);
		void setViewMatrix(int shader);
		void setSkyboxViewMatrix(int shader);
		void setProjectionMatrix(int shader);
        void setWidth(int width);
        void setHeight(int height);
		float getFOV();
};