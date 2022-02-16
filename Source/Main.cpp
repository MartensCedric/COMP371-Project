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

#define SHOW_GUI 0

#if SHOW_GUI == 1
#include <nanogui/nanogui.h>
#endif

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
#include <sstream>
#include <iomanip> 

WorldModel* world = nullptr;

#if SHOW_GUI == 1
nanogui::Screen *screen = nullptr;
nanogui::FormHelper *gui = nullptr;
nanogui::ref<nanogui::Window> nanoguiWindow = nullptr;

struct SliderCombo {
	nanogui::Slider *slider;
	nanogui::TextBox *tb;
};

SliderCombo* slider1;
SliderCombo* slider2;
SliderCombo* slider3;
SliderCombo* slider4;
SliderCombo* slider5;
SliderCombo* slider6;
SliderCombo* slider7;
SliderCombo* slider8;
SliderCombo* slider9;
#endif

double currentYPos;
double previousYPos = -1;
int randomX;
int randomY;
double currentVariation = 0;
bool leftMouseClick = false;
Camera* currentCamera = nullptr;
Camera* playerCamera = nullptr;
Camera* topCamera = nullptr;
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

#if SHOW_GUI == 1
SliderCombo* add_slider(float* value, float min, float max) {
	/* Create an empty panel with a horizontal layout */
	nanogui::Widget *panel = new nanogui::Widget(nanoguiWindow);
	panel->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	SliderCombo* slidercombo = new SliderCombo();

	/* Add a slider and set defaults */
	slidercombo->slider = new nanogui::Slider(panel);
	slidercombo->slider->set_value(*value);
	slidercombo->slider->set_range(std::pair<float, float>(min, max));
	slidercombo->slider->set_fixed_width(100);

	/* Add a textbox and set defaults */
	slidercombo->tb = new nanogui::TextBox(panel);
	slidercombo->tb->set_fixed_size(nanogui::Vector2i(65, 25));
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << *value;
	std::string s = stream.str();
	slidercombo->tb->set_value(s);

	nanogui::TextBox* tb = slidercombo->tb;

	/* Propagate slider changes to the text box */
	slidercombo->slider->set_callback([tb, value](float v) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << v;
		std::string s = stream.str();
		tb->set_value(s);

		*value = v;
	});

	gui->add_widget("Slider", panel);

	return slidercombo;
}

void update_parameters() {
	world->updateParameters();
}

void reset_sliders() {
	slider1->slider->set_value(world->default_parameters.terrainHeight);
	slider2->slider->set_value(world->default_parameters.waterHeight);
	slider3->slider->set_value(world->default_parameters.forestFrequency);
	slider4->slider->set_value(world->default_parameters.forestDensity);
	slider5->slider->set_value(world->default_parameters.penguinFrequency);
	slider6->slider->set_value(world->default_parameters.penguinDensity);

	std::stringstream stream1;
	stream1 << std::fixed << std::setprecision(2) << world->default_parameters.terrainHeight;
	std::string s1 = stream1.str();
	slider1->tb->set_value(s1);

	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(2) << world->default_parameters.waterHeight;
	std::string s2 = stream2.str();
	slider2->tb->set_value(s2);

	std::stringstream stream3;
	stream3 << std::fixed << std::setprecision(2) << world->default_parameters.forestFrequency;
	std::string s3 = stream3.str();
	slider3->tb->set_value(s3);

	std::stringstream stream4;
	stream4 << std::fixed << std::setprecision(2) << world->default_parameters.forestDensity;
	std::string s4 = stream4.str();
	slider4->tb->set_value(s4);

	std::stringstream stream5;
	stream5 << std::fixed << std::setprecision(2) << world->default_parameters.penguinFrequency;
	std::string s5 = stream5.str();
	slider5->tb->set_value(s5);

	std::stringstream stream6;
	stream6 << std::fixed << std::setprecision(2) << world->default_parameters.penguinDensity;
	std::string s6 = stream6.str();
	slider6->tb->set_value(s6);
}
#endif

bool disableWalking = false;
bool topCameraUsed = false;
bool mainCameraAllowed = false;
glm::vec3 savedLookVec;
glm::vec3 savedPosition;

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
}

//The purpose of the cursorPositionCallback is to track the mouse position, determine the variation in Y position, and to set the camera's FOV based on this variation
void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) 
{
	currentYPos = yPos;

	if (previousYPos != -1) {
		currentVariation = currentYPos - previousYPos;
	}

	if (leftMouseClick == true) {
		currentCamera->setFOV((currentCamera->getFOV())- currentVariation/1000);
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
	int cloudsShader = compileAndLinkShaders("../Shaders/textureLight.vshader", "../Shaders/clouds.fshader");
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
	currentCamera = new Camera(windowWidth, windowHeight);
	playerCamera = currentCamera;
	playerCamera->position = glm::vec3(-12, 0, 15);
	topCamera = new Camera(windowWidth, windowHeight);
	world = new WorldModel();

	Skybox skybox;
	skybox.setShader(skyboxShader);
	skybox.setCamera(currentCamera);
	skybox.setTexture(skyboxCubeMap);
	world->setCamera(currentCamera);

	world->setWaterShader(waterShader);
	world->setTerrainShader(terrainShader);
	world->setPenguinBeaksShader(passthroughShader);

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
	float initial_y = world->getTerrainHeight(currentCamera->position.x, currentCamera->position.z) + 5.0f;
	currentCamera->position = glm::vec3(currentCamera->position.x, initial_y, currentCamera->position.z);

	#if SHOW_GUI == 1
	
	// Create a GLFWwindow object
    GLFWwindow* guiwindow = glfwCreateWindow(314, 700, "GUI", nullptr, nullptr);
    if (guiwindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(guiwindow);

	// Create a nanogui screen and pass the glfw pointer to initialize
    screen = new nanogui::Screen();
    screen->initialize(guiwindow, true);

	glfwSwapInterval(0);
    glfwSwapBuffers(guiwindow);
	
    gui = new nanogui::FormHelper(screen);
    nanoguiWindow = gui->add_window(nanogui::Vector2i(10, 10), "Customization");
    
	gui->add_group("Terrain Height");
	slider1 = add_slider(&(world->parameters.terrainHeight), 1, 20);

	gui->add_group("Water Height");
	slider2 = add_slider(&(world->parameters.waterHeight), -5, 0);

	gui->add_group("Forest Frequency");
	slider3 = add_slider(&(world->parameters.forestFrequency), -1, 1);

	gui->add_group("Forest Density");
	slider4 = add_slider(&(world->parameters.forestDensity), 1, 1000);

	gui->add_group("Penguin Frequency");
	slider5 = add_slider(&(world->parameters.penguinFrequency), 0, 1);

	gui->add_group("Penguin Density");
	slider6 = add_slider(&(world->parameters.penguinDensity), 1, 20);

	gui->add_group("Terrain Spread");
	slider7 = add_slider(&(world->parameters.terrainSpread), 1, 10);

	gui->add_group("Forest Spread");
	slider8 = add_slider(&(world->parameters.forestSpread), 1, 10);

	gui->add_group("Seed");
	slider9 = add_slider(&(world->parameters.seed), 0, 100);
	
    gui->add_button("Reset", reset_sliders);
	gui->add_button("Confirm", update_parameters);

    screen->set_visible(true);
	screen->perform_layout();
    nanoguiWindow->center();
	screen->clear();
    
    glfwSetCursorPosCallback(guiwindow, [](GLFWwindow *, double x, double y) {
        screen->cursor_pos_callback_event(x, y);
    });

    glfwSetMouseButtonCallback(guiwindow, [](GLFWwindow *, int button, int action, int modifiers) {
        screen->mouse_button_callback_event(button, action, modifiers);
    });

    glfwSetKeyCallback(guiwindow, [](GLFWwindow *, int key, int scancode, int action, int mods) {
        screen->key_callback_event(key, scancode, action, mods);
	});

    glfwSetCharCallback(guiwindow, [](GLFWwindow *, unsigned int codepoint) {
        screen->char_callback_event(codepoint);
    });

    glfwSetDropCallback(guiwindow, [](GLFWwindow *, int count, const char **filenames) {
        screen->drop_callback_event(count, filenames);
    });

    glfwSetScrollCallback(guiwindow, [](GLFWwindow *, double x, double y) {
        screen->scroll_callback_event(x, y);
	});

    glfwSetFramebufferSizeCallback(guiwindow, [](GLFWwindow *, int width, int height) {
        screen->resize_callback_event(width, height);
    });

	#endif

    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {

		glfwMakeContextCurrent(window);

		world->setCamera(currentCamera);
		world->setSkybox(skyboxCubeMap);
		world->setLight(worldLight);

		double newTime = glfwGetTime();
		delta = newTime - currentTime;
		currentTime = newTime;
		sunTheta += 0.2f * delta;
		time_passed += delta;
		world->setTimePassed(time_passed);

		worldLight->direction = glm::vec3(sin(sunTheta), -cos(sunTheta), 0);
		worldLight->position = 30.0f * -glm::normalize(worldLight->direction) + currentCamera->position; 
		
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

		#if SHOW_GUI == 1
		glfwMakeContextCurrent(guiwindow);
		// Detect inputs
        glfwPollEvents();

		// Draw nanogui
        screen->draw_setup();
		screen->draw_widgets();
		#endif

		glfwMakeContextCurrent(window);
		// Detect inputs
        glfwPollEvents();

		for (auto it = world->spheres.begin(); it != world->spheres.end(); it++)
		{
			(*it)->setShader(showLight ? lightAffectedShader : passthroughShader);
		}
		for (auto it = world->clouds.begin(); it != world->clouds.end(); it++)
		{
			(*it)->setShader(cloudsShader);
		}
		world->plane->setShader(waterShader);
 
		world->setPenguinBeaksShader(passthroughShader);

		world->draw();
			
        // End frame
        glfwSwapBuffers(window);

		#if SHOW_GUI == 1
		glfwSwapBuffers(guiwindow);
		#endif

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
				glm::mat4 panRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), -currentCamera->up);
				glm::vec3 newDirection(glm::normalize(panRotation * glm::vec4(panDirection, 1.0f)) * 1000.0f);
				glm::vec3 newLookAt = newDirection + currentCamera->position;
				currentCamera->lookAtPos = newLookAt;
			}
			else {
				isPanning = true;
				xPanStart = xCursor;
				panDirection = glm::normalize(currentCamera->lookAtPos - currentCamera->position);
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
				glm::mat4 tiltRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), glm::cross(tiltDirection, currentCamera->up));

				glm::vec3 newDirection(glm::normalize(tiltRotation * glm::vec4(tiltDirection, 1.0f)) * 1000.0f);
				glm::vec3 newLookAt = newDirection + currentCamera->position;
				currentCamera->lookAtPos = newLookAt;

			}
			else {
				isTilting = true;
				yTiltStart = yCursor;
				tiltDirection = currentCamera->lookAtPos - currentCamera->position;
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

		//World Camera position
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			disableWalking = true;
			topCameraUsed = true;
			mainCameraAllowed = true;
			currentCamera = topCamera;
		}

		//Return to player camera position
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && topCameraUsed && mainCameraAllowed)
		{
			disableWalking = false;
			mainCameraAllowed = false; //if main camera is being used, then must use top camera before using main camera again

			currentCamera = playerCamera;
		}
		
		//Character controls

		// move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !disableWalking)
		{
			glm::vec3 lookVec = glm::normalize(currentCamera->lookAtPos - currentCamera->position);
			float x = currentCamera->position.x + walkSpeed * delta * lookVec.x;
			float z = currentCamera->position.z + walkSpeed * delta * lookVec.z;

			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				currentCamera->position = nextPosition;
				currentCamera->lookAtPos = currentCamera->position + lookVec;
			}

		}

		// move backwards
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !disableWalking)
		{

			glm::vec3 lookVec = glm::normalize(currentCamera->lookAtPos - currentCamera->position);
			float x = currentCamera->position.x - walkSpeed * delta * lookVec.x;
			float z = currentCamera->position.z - walkSpeed * delta * lookVec.z;
			
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				currentCamera->position = nextPosition;
				currentCamera->lookAtPos = currentCamera->position + lookVec;
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !disableWalking)
		{

			glm::vec3 lookVec = glm::normalize(currentCamera->lookAtPos - currentCamera->position);
			glm::vec3 movementVec = glm::normalize(glm::cross(currentCamera->up, lookVec));
			float x = currentCamera->position.x + walkSpeed * delta * movementVec.x;
			float z = currentCamera->position.z + walkSpeed * delta * movementVec.z;
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				currentCamera->position = nextPosition;
				currentCamera->lookAtPos = currentCamera->position + lookVec;
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !disableWalking)
		{
			glm::vec3 lookVec = glm::normalize(currentCamera->lookAtPos - currentCamera->position);
			glm::vec3 movementVec = glm::normalize(glm::cross(lookVec, currentCamera->up));
			float x = currentCamera->position.x + walkSpeed * delta * movementVec.x;
			float z = currentCamera->position.z + walkSpeed * delta * movementVec.z;
			glm::vec3 nextPosition = glm::vec3(x, world->getTerrainHeight(x, z) + cameraHeightFromTerrain, z);

			if (!collidesWithModels(nextPosition))
			{
				currentCamera->position = nextPosition;
				currentCamera->lookAtPos = currentCamera->position + lookVec;
			}
		}

		//Move clouds
		for (std::vector<Model*>::iterator it = world->clouds.begin(); it != world->clouds.end(); it++)
		{
			(*it)->translate(0, 0, 0.06);
		}

		for (std::vector<Model*>::iterator it = world->clouds.begin(); it != world->clouds.end(); it++)
		{
			double randomX = rand() % 201 + (-100);
			double randomY = rand() % 9 + (-4);

			if ( (*it)->objTransMat[2, 3].z > ((double)(currentCamera->position.z) + 100)) {
				(*it)->objTransMat[2, 3].z = -100;
				(*it)->objTransMat[2, 3].x = randomX;
				(*it)->objTransMat[2, 3].y = randomY;
			}	
		}
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
