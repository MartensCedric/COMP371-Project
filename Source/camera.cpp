#include <GL/glew.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <iostream>
class Camera {
    public:
        GLfloat speed;
        glm::vec3 position;
        glm::vec3 lookAtPos;
        // which direction is the top of the camera
        glm::vec3 up;
        int shaderProgram;

        Camera() {
        }

        Camera(int shaderProgram) : 
            speed(0.1f), 
            position(0.0f, 5.0f, 15.0f),
            lookAtPos(0.0f, 0.0f, -1.0f),
            up(0.0f, 1.0f, 0.0f),
            shaderProgram(shaderProgram)
        {
            // With this enabled (surfaces with vertices in counter clockwise direction will render)
			// Therefore the back of a surface will not render (more efficient)
            glEnable(GL_CULL_FACE); 
            
            //With this enabled, object behind other objects will not be rendered
        	glEnable(GL_DEPTH_TEST);

            // greyish background color
            glClearColor(0.2f, 0.29f, 0.29f, 1.0f);

            // Set projection matrix for the shader (in this case we use perspective projection)
            glm::mat4 projectionMatrix = glm::perspective(
                70.0f,            // field of view in degrees
                1024.0f / 768.0f, // aspect ratio
                0.01f, 100.0f     // near and far (near > 0)
            );
            GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
            glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        }

        void MoveForward() {
            position += speed * lookAtPos;
        }

	    void MoveBack() {
            position -= speed * lookAtPos;
        }

	    void MoveLeft() {
    		position -= glm::normalize(glm::cross(lookAtPos, up)) * speed;
        }

        void MoveRight() {
    		position += glm::normalize(glm::cross(lookAtPos, up)) * speed;
        }

        void update() {
			std::cout << "x " << lookAtPos.x << std::endl;
			std::cout << "y " << lookAtPos.y << std::endl;
			std::cout << "z " << lookAtPos.z << std::endl;
            // Set initial view matrix (because this is running in the "main while loop", it will update every frame)
            glm::mat4 viewMatrix = lookAt(
                position, // eye
                lookAtPos + position, // center
                up // up
            ); 
            GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);	
        }
};
