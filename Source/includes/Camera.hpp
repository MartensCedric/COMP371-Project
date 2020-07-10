#include <GL/glew.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    public:
        GLfloat speed;
        glm::vec3 position;
        glm::vec3 lookAtPos;
        glm::vec3 up;
        int shaderProgram;

        Camera();
        Camera(int shaderProgram);
        void moveForward();
        void moveBack();
        void moveLeft();
        void moveRight();
        void reset();
};
