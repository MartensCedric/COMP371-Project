//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hefllo-Triangle

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "includes/Camera.hpp"
#include "includes/WorldModel.hpp"
#include "includes/Skybox.hpp"
#include "includes/TreeModel.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/Shader.hpp"

#include "../Source/includes/Camera.hpp"
#include "../Source/includes/WorldModel.hpp"
#include "../Source/includes/Skybox.hpp"
#include "../Source/includes/TreeModel.hpp"

#endif

#define GL_GLEXT_PROTOTYPES

// GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <GLFW/glfw3.h> 

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

extern struct BoxCollider;

WorldModel* world = nullptr;

double currentYPos;
double previousYPos = -1;
int randomX;
int randomY;
double currentVariation = 0;
bool leftMouseClick = false;
Camera* camera = nullptr;
BoxCollider cameraCollider;
int windowWidth = 1024;
int windowHeight = 768;

double delta = 0.16;
float time_passed = 0;

int maxOffset = 2;
float walkSpeed = 7.f;
float cameraHeightFromTerrain = 5.0f;

float sunTheta = 0;

bool showTexture = true;
bool isTextureToggled = false;

bool showLight = true;
bool isLightToggled = false;

bool hasBottomMovedForward = false;
bool hasBottomMovedBackward = false;
bool hasBottomMovedRight = false;
bool hasBottomMovedLeft = false;

bool hasTopMovedForward = false;
bool hasTopMovedBackward = false;
bool hasTopMovedRight = false;
bool hasTopMovedLeft = false;

bool hasMovedForward = false;
bool hasMovedBackward = false;
bool hasMovedRight = false;
bool hasMovedLeft = false;

bool hasTurnedRight = false;
bool hasTurnedLeft = false;

void window_size_callback(GLFWwindow* window, int width, int height) {
	float scale = std::min(((float)width)/windowWidth, ((float)height)/windowHeight);
	float scaledWidth = windowWidth*scale;
	float scaledHeight = windowHeight*scale;
	glViewport((width - scaledWidth)/2, (height - scaledHeight)/2, scaledWidth, scaledHeight);
}

bool models_sort(Model* model1, Model* model2) { 
	// Apply the Model matrix to the center of the model
	// To get its position in the World coordinates system 
	glm::vec4 new_model1_pos = model1->getModelMatrix() * glm::vec4(0, 0, 0, 1);
	glm::vec4 new_model2_pos = model2->getModelMatrix() * glm::vec4(0, 0, 0, 1);
	
	return (new_model1_pos.z < new_model2_pos.z);
}

bool collidesWithModels(glm::vec3 position)
{
	for (auto it = world->models.begin(); it != world->models.end(); it++)
		if ((*it)->collidesWith(position, &cameraCollider))
			return true;
	return false;
}

// Callbacks for keys
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_ENTER) &&
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS &&
		!hasTurnedLeft
	) {
		hasTurnedLeft = true;
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, 5);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		hasTurnedLeft = false;
	}

	// Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_ENTER) &&
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
		!hasTurnedRight
	) {
		hasTurnedRight = true;
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, -5);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		hasTurnedRight = false;
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, 5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, -5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, 5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, -5);
		}
	}

	// NOTE: clockwise is defined relative to the origin vectors outward direction of corresponding axis
	// Rotate World Orientation anti-clockwise about Y axis
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world->rotate(0, 1, 0, -5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	// Rotate World Orientation clockwise about Y axis
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world->rotate(0, 1, 0, 5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	// Rotate World Orientation clockwise about X axis
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		world->rotate(1, 0, 0, -5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	// Rotate World Orientation anti-clockwise about X axis
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		world->rotate(1, 0, 0, 5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	// Move world back
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
	{
		world->translate(0, 0, -1);
	}
	// move world forward
	else if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
	{
		world->translate(0, 0, 1);
	}

	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		world->reset();
	}

	// Scale Up
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->scale(1.05, 1.05, 1.05);
		}
	}
	
	// Scale Down
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->scale(0.95, 0.95, 0.95);
		}
	}
	
	// Switch to lines rendering mode
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Switch to triangle rendering mode
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Switch to points rendering mode
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	// Toggle Light
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !isLightToggled) {
		isLightToggled = true;
		showLight = !showLight;
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
		isLightToggled = false;
	}

	// Toggle Texture
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !isTextureToggled) {
		isTextureToggled = true;
		showTexture = !showTexture;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
		isTextureToggled = false;
	}

		// ------------------------------------------------ FULL CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !hasMovedForward)
		{
			hasMovedForward = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !hasMovedBackward)
		{
			hasMovedBackward = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !hasMovedLeft)
		{
			hasMovedLeft = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !hasMovedRight)
		{
			hasMovedRight = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}
}

//The purpose of the cursorPositionCallback is to track the mouse position, determine the variation in Y position, and to set the camera's FOV based on this variation
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) 
{
	currentYPos = yPos;

	if (previousYPos != -1) {
		currentVariation = currentYPos - previousYPos;
	}

	if (leftMouseClick == true) {
		camera->setFOV((camera->getFOV())- currentVariation/1000);
	}
}

//The purpose of the mouseButtonCallback method is to detect a left click and signal the initial y position of the cursor through the use of the cursor callback method
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		previousYPos = currentYPos;
		leftMouseClick = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		previousYPos = -1;
		leftMouseClick = false;
	}
}

void setWorldMatrix(int shaderProgram, glm::mat4 worldMatrix)
{
	glUseProgram(shaderProgram);
	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

int main(int argc, char*argv[])
{
	cameraCollider.width = 5;
	cameraCollider.length = 5;
	cameraCollider.height = 100;

    // Initialize GLFW and OpenGL version
    glfwInit();
	glfwSetTime(0);

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(PLATFORM_OSX)	
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Comp371 - Final Project", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

	double currentTime = glfwGetTime();

	int skyboxCubeMap = loadSkybox();

    // Compile and link shaders here ...
	int lightAffectedShader = compileAndLinkShaders("../Shaders/phong.vshader", "../Shaders/phong.fshader");
	int textureShader = compileAndLinkShaders("../Shaders/texture.vshader", "../Shaders/texture.fshader");
	int textureLightShader = compileAndLinkShaders("../Shaders/textureLight.vshader", "../Shaders/textureLight.fshader");
	int passthroughShader = compileAndLinkShaders("../Shaders/passthrough.vshader", "../Shaders/passthrough.fshader");
	int shadowShader = compileAndLinkShaders("../Shaders/shadow.vshader", "../Shaders/shadow.fshader");
	int skyboxShader = compileAndLinkShaders("../Shaders/skybox.vshader", "../Shaders/skybox.fshader");
	int terrainShader = compileAndLinkShaders("../Shaders/terrain.vshader", "../Shaders/terrain.fshader");
	int waterShader = compileAndLinkShaders("../Shaders/water.vshader", "../Shaders/water.fshader", "../Shaders/water.gshader");

	// Two Pass Shadow Map. Code adapted from learnopengl.com
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int shadowMapFBO;
	glGenFramebuffers(1, &shadowMapFBO);
	
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Attach it to framebuffer's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE); // We don't need color buffer
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------Camera setup----------
	camera = new Camera(windowWidth, windowHeight);
	world = new WorldModel();

	Skybox skybox;
	skybox.setShader(skyboxShader);
	skybox.setCamera(camera);
	skybox.setTexture(skyboxCubeMap);
	world->setCamera(camera);

	world->setAxesShader(passthroughShader);
	world->setGridShader(passthroughShader);
	world->setWaterShader(waterShader);
	world->setTerrainShader(terrainShader);
	//world->setPenguinBeaksShader(passthroughShader);

	DirectionalLight* worldLight = new DirectionalLight();
	world->setLight(worldLight);
	world->setSkybox(skyboxCubeMap);
	
	// Variables for Tilt/Pan
	double xCursor, yCursor;
	double xPanStart = -1;
	double yTiltStart = -1;
	bool isPanning = false;
	bool isTilting = false;
	glm::vec3 panDirection = glm::vec3(1.0f);
	glm::vec3 tiltDirection = glm::vec3(1.0f);
	float initial_y = world->getTerrainHeight(camera->position.x, camera->position.z) + 5.0f;
	camera->position = glm::vec3(camera->position.x, initial_y, camera->position.z);

	// Create a GLFWwindow object
    GLFWwindow* guiwindow = glfwCreateWindow(314, 363, "GUI", nullptr, nullptr);
    if (guiwindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(guiwindow);

	// Create a nanogui screen and pass the glfw pointer to initialize
    screen = new nanogui::Screen();
    screen->initialize(guiwindow, true);

	// Create nanogui gui
    bool enabled = true;

	enum test_enum {
    	Item1 = 0,
    	Item2,
    	Item3
	};

	glfwSwapInterval(0);
    glfwSwapBuffers(guiwindow);

	bool bvar = true;
	int ivar = 12345678;
	test_enum enumval = Item2;
	nanogui::Color colval(0.5f, 0.5f, 0.7f, 1.f);

    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->add_window(nanogui::Vector2i(10, 10), "Customization");
    gui->add_group("Basic types");
    gui->add_variable("bool", bvar);
    
    gui->add_group("Validating fields");
    gui->add_variable("int", ivar)->set_spinnable(true);
   
    gui->add_group("Complex types");
    gui->add_variable("Enumeration", enumval, enabled)->set_items({ "Item 1", "Item 2", "Item 3" });
    gui->add_variable("Color", colval)
       ->set_final_callback([](const nanogui::Color &c) {
             std::cout << "ColorPicker Final Callback: ["
                       << c.r() << ", "
                       << c.g() << ", "
                       << c.b() << ", "
                       << c.w() << "]" << std::endl;
         });

    gui->add_group("Other widgets");

	/* Create an empty panel with a horizontal layout */
	nanogui::Widget *panel = new nanogui::Widget(nanoguiWindow);
	panel->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	/* Add a slider and set defaults */
	nanogui::Slider *slider = new nanogui::Slider(panel);
	slider->set_value(0.5f);
	slider->set_fixed_width(100);

	/* Add a textbox and set defaults */
	nanogui::TextBox *tb = new nanogui::TextBox(panel);
	tb->set_fixed_size(nanogui::Vector2i(65, 25));
	tb->set_value("50");
	tb->set_units("%");

	/* Propagate slider changes to the text box */
	slider->set_callback([tb](float value) {
		tb->set_value(std::to_string((int) (value * 100)));
	});

	gui->add_widget("Slider", panel);

    gui->add_button("Reset", []() { std::cout << "Button pressed." << std::endl; });

    screen->set_visible(true);
	screen->perform_layout();
    nanoguiWindow->center();
	screen->clear();
    
    glfwSetCursorPosCallback(guiwindow,
            [](GLFWwindow *, double x, double y) {
            screen->cursor_pos_callback_event(x, y);
        }
    );

    glfwSetMouseButtonCallback(guiwindow,
        [](GLFWwindow *, int button, int action, int modifiers) {
            screen->mouse_button_callback_event(button, action, modifiers);
        }
    );

    glfwSetKeyCallback(guiwindow,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            screen->key_callback_event(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(guiwindow,
        [](GLFWwindow *, unsigned int codepoint) {
            screen->char_callback_event(codepoint);
        }
    );

    glfwSetDropCallback(guiwindow,
        [](GLFWwindow *, int count, const char **filenames) {
            screen->drop_callback_event(count, filenames);
        }
    );

    glfwSetScrollCallback(guiwindow,
        [](GLFWwindow *, double x, double y) {
            screen->scroll_callback_event(x, y);
       }
    );

    glfwSetFramebufferSizeCallback(guiwindow,
        [](GLFWwindow *, int width, int height) {
            screen->resize_callback_event(width, height);
        }
	);

    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {
		glfwMakeContextCurrent(window);
		
		double newTime = glfwGetTime();
		delta = newTime - currentTime;
		currentTime = newTime;
		sunTheta += 0.2f * delta;
		time_passed += delta;
		world->setTimePassed(time_passed);

		worldLight->direction = glm::vec3(sin(sunTheta), -cos(sunTheta), 0);
		worldLight->position = 30.0f * -glm::normalize(worldLight->direction) + camera->position; 
		
		int modelShader = passthroughShader;

		if (showLight && showTexture)
		{
			modelShader = textureLightShader;
		}
		else if (showLight)
		{
			modelShader = lightAffectedShader;
		}
		else if (showTexture)
		{
			modelShader = textureShader;
		}

		// Each frame, reset color of each pixel to glClearColor and reset the depth-
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
	
		glBindTexture(GL_TEXTURE_2D, depthMap);

		world->terrain->setShader(terrainShader);
		
		for (auto it = world->models.begin(); it != world->models.end(); it++)
			(*it)->setShader(modelShader);

		
		glDepthMask(GL_FALSE);
		glUseProgram(skyboxShader);
		glm::vec3 lightDirection = worldLight->direction;
		int lightDirectionLocation = glGetUniformLocation(skyboxShader, "lightDirection");
		glUniform3fv(lightDirectionLocation, 1, &lightDirection[0]);
		skybox.draw();
		glDepthMask(GL_TRUE);

		glfwMakeContextCurrent(guiwindow);
		// Detect inputs
        glfwPollEvents();

		// Draw nanogui
        screen->draw_setup();
		screen->draw_widgets();

		glfwMakeContextCurrent(window);
		// Detect inputs
        glfwPollEvents();

		world->draw();
			
        // End frame
        glfwSwapBuffers(window);
		glfwSwapBuffers(guiwindow);

		glfwGetCursorPos(window, &xCursor, &yCursor);
        // Detect inputs
        glfwPollEvents();

		//Handle Inputs

		//Terminate program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (isPanning)
			{
				// If the mouse is paning (left/right) move the camera around the axis -Camera-up 
				double dx = xCursor - xPanStart;
				double angleDegrees = (dx/10.f);
				glm::mat4 panRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), -camera->up);
				glm::vec3 newDirection(glm::normalize(panRotation * glm::vec4(panDirection, 1.0f)) * 1000.0f);
				glm::vec3 newLookAt = newDirection + camera->position;
				camera->lookAtPos = newLookAt;
			}
			else {
				isPanning = true;
				xPanStart = xCursor;
				panDirection = glm::normalize(camera->lookAtPos - camera->position);
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			if (isPanning)
			{
				isPanning = false;
				xPanStart = -1;
				panDirection = glm::vec3(1.0f);
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			if (isTilting)
			{
				// If the mouse is tilting (up/down) move the camera around the axis LookAt-Direction X Camera-up 
				double dy = yTiltStart - yCursor;
				double angleDegrees = (dy * 3.f) * delta;
				glm::mat4 tiltRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), glm::cross(tiltDirection, camera->up));

				glm::vec3 newDirection(glm::normalize(tiltRotation * glm::vec4(tiltDirection, 1.0f)) * 1000.0f);
				glm::vec3 newLookAt = newDirection + camera->position;
				camera->lookAtPos = newLookAt;

			}
			else {
				isTilting = true;
				yTiltStart = yCursor;
				tiltDirection = camera->lookAtPos - camera->position;
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
		{
			if (isTilting)
			{
				isTilting = false;
				yTiltStart = -1;
				tiltDirection = glm::vec3(1.0f);
			}
		}
		
		//Character controls

		// move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			glm::vec3 lookVec = glm::normalize(camera->lookAtPos - camera->position);
			float x = camera->position.x + walkSpeed * delta * lookVec.x;
			float z = camera->position.z + walkSpeed * delta * lookVec.z;

			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				camera->position = nextPosition;
				camera->lookAtPos = camera->position + lookVec;
			}
		}

		// move backwards
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			glm::vec3 lookVec = glm::normalize(camera->lookAtPos - camera->position);
			float x = camera->position.x - walkSpeed * delta * lookVec.x;
			float z = camera->position.z - walkSpeed * delta * lookVec.z;
			
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				camera->position = nextPosition;
				camera->lookAtPos = camera->position + lookVec;
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			glm::vec3 lookVec = glm::normalize(camera->lookAtPos - camera->position);
			glm::vec3 movementVec = glm::normalize(glm::cross(camera->up, lookVec));
			float x = camera->position.x + walkSpeed * delta * movementVec.x;
			float z = camera->position.z + walkSpeed * delta * movementVec.z;
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				camera->position = nextPosition;
				camera->lookAtPos = camera->position + lookVec;
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			glm::vec3 lookVec = glm::normalize(camera->lookAtPos - camera->position);
			glm::vec3 movementVec = glm::normalize(glm::cross(lookVec, camera->up));
			float x = camera->position.x + walkSpeed * delta * movementVec.x;
			float z = camera->position.z + walkSpeed * delta * movementVec.z;
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				camera->position = nextPosition;
				camera->lookAtPos = camera->position + lookVec;
			}
		}


		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && 
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (!glfwGetKey(window, GLFW_KEY_ENTER) && 
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && 
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		//move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}
		}

		//move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, -1, 0);
			}
		}
			
		// Scale Up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->scale(1.05, 1.05, 1.05);
			}
		}
		
		// Scale Down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->scale(0.95, 0.95, 0.95);
			}
		}
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}