#include "includes/Model.hpp"

Model::Model() {}

/**
* Model Class
* This is an OpenGL wrapper which allows you to create models with hierarchical modeling.
* The vertices must be specified as well as a routine that draws said model.
*/
Model::Model(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera))
{
	drawFunction = drawFunc;
	// Create a vertex array
	GLuint modelVAO;   //Create a VAO 
	glGenVertexArrays(1, &modelVAO); //Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(modelVAO);  //Tell openGL to use this VAO until I decide to change it (openGL is state machine)

	GLuint modelVBO;  //Create a VBO  (VBO's connect to a single VAO)
	glGenBuffers(1, &modelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

	vaoId = modelVAO;
	this->vertexCount = vertexCount;
}

/**
* Sets the camera that renders this model. Useful to get the view matrix
*/
void Model::setCamera(Camera* camera)
{
	this->camera = camera;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->setCamera(camera);
	}
}

bool Model::collidesWith(glm::vec3 modelPosition, BoxCollider* otherCollider)
{
	if (otherCollider == nullptr || this->collider == nullptr)
		return false;

	float thisX = this->objTransMat[3][0];
	float thisY = this->objTransMat[3][1];
	float thisZ = this->objTransMat[3][2];

	float thatX = modelPosition.x;
	float thatY = modelPosition.y;
	float thatZ = modelPosition.z;

	float xLeft1 = thisX - this->collider->width / 2.0f;
	float xRight1 = thisX + this->collider->width / 2.0f;

	float xLeft2 = thatX - otherCollider->width / 2.0f;
	float xRight2 = thatX + otherCollider->width / 2.0f;

	bool xIntersects = intersects(xLeft1, xLeft2, xRight2) || intersects(xRight1, xLeft2, xRight2);


	float yLeft1 = thisY - this->collider->height / 2.0f;
	float yRight1 = thisY + this->collider->height / 2.0f;

	float yLeft2 = thatY - otherCollider->height / 2.0f;
	float yRight2 = thatY + otherCollider->height / 2.0f;

	bool yIntersects = intersects(yLeft1, yLeft2, yRight2) || intersects(yRight1, yLeft2, yRight2);



	float zLeft1 = thisZ - this->collider->length / 2.0f;
	float zRight1 = thisZ + this->collider->length / 2.0f;

	float zLeft2 = thatZ - otherCollider->length / 2.0f;
	float zRight2 = thatZ + otherCollider->length / 2.0f;

	bool zIntersects = intersects(zLeft1, zLeft2, zRight2) || intersects(zRight1, zLeft2, zRight2);

	return xIntersects && yIntersects && zIntersects;
}

bool Model::collidesWith(Model* otherModel)
{
	if (this->collider == nullptr || otherModel->collider == nullptr)
		return false;

	float thisX = otherModel->objTransMat[3][0];
	float thisY = otherModel->objTransMat[3][1];
	float thisZ = otherModel->objTransMat[3][2];
	glm::vec3 position(thisX, thisY, thisZ);

	return collidesWith(position, otherModel->collider);
}

/**
* Sets the shader for the model and its children
*/
void Model::setShader(int shaderProgram)
{
	shaderId = shaderProgram;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->setShader(shaderProgram);
	}
};

/**
* Sets the shader for the model and its children
*/
void Model::setTexture(GLuint texture)
{
	textureId = texture;

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->setTexture(texture);
	}
};

void Model::setLight(DirectionalLight* light)
{
	this->light = light;
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->setLight(light);
	}
}

void Model::setSkybox(int skybox)
{
	this->skybox = skybox;
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->setSkybox(skybox);
	}
}

void Model::setTimePassed(float time_passed)
{
	this->time_passed = time_passed;
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->setTimePassed(time_passed);
	}
}

/**
* Draws the model. Binds the correct shader and VAO, it will also draw all the children.
*/
void Model::draw()
{
	glUseProgram(shaderId);
	glActiveTexture(GL_TEXTURE1);
	int modelTextureLoc = glGetUniformLocation(shaderId, "textureSampler");
	glUniform1i(modelTextureLoc, 1);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glActiveTexture(GL_TEXTURE2);
	int skyboxLoc = glGetUniformLocation(shaderId, "skybox");
	glUniform1i(skyboxLoc, 2);

	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);


	glm::mat4 lightProjection = glm::ortho(
		-100.f, 100.f, -100.f, 100.f,
		0.01f, 800.f
	);         // near and far (near > 0)
	glm::mat4 lightView = glm::lookAt(glm::vec3(light->position), camera->position, glm::vec3(0, 1, 0));

	glm::mat4 lightSpaceMatrix = lightProjection * lightView * getModelMatrix();
	int lightSpaceLocationShadow = glGetUniformLocation(shaderId, "light_proj_view_matrix");
	glUniformMatrix4fv(lightSpaceLocationShadow, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

	glm::vec3 lightDirection = this->light->direction;
	int lightDirectionLocation = glGetUniformLocation(shaderId, "lightDirection");
	glUniform3fv(lightDirectionLocation, 1, &lightDirection[0]);


	glm::vec3 eyePosition = camera->position;
	GLuint eyePositionLocation = glGetUniformLocation(shaderId, "eyePosition");
	glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);

	GLuint dtLoc = glGetUniformLocation(shaderId, "time_passed");
	glUniform1f(dtLoc, time_passed);

	glBindVertexArray(vaoId);
	this->camera->setProjectionMatrix(shaderId);
	this->camera->setViewMatrix(shaderId);
	drawFunction(vertexCount, shaderId, this->getModelMatrix(), this->camera);

	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw();
	}
}

/**
* Scales the model
*/
void Model::scale(float x, float y, float z)
{
	this->objScaleMat = glm::scale(objScaleMat, glm::vec3(x, y, z));
}

/**
* Rotates the model
*/
void Model::rotate(float x, float y, float z, float angle)
{
	//Implement by modifying objRotMat
	float radianAngle = glm::radians(angle);
	glm::vec3 myRotationAxis(x, y, z);
	this->objRotMat = glm::rotate(objRotMat, radianAngle, myRotationAxis);
}

/**
* Translates the model
*/
void Model::translate(float x, float y, float z)
{
	this->objTransMat = glm::translate(objTransMat, glm::vec3(x, y, z));
}

/**
* Adds a child in the hierarchy for this model.
*/
void Model::addChild(Model* child)
{
	child->parent = this;
	children.push_back(child);
}



/**
* Gets the model matrix for this model.
* The model matrix is used to get the coordinate transform of this model in respect to the world.
* Children transformations are done first (at the right). The process is recursive.
*/
glm::mat4 Model::getModelMatrix() const
{
	if (this->parent == nullptr)
		return objTransMat * objRotMat * objScaleMat;

	return this->parent->getModelMatrix() * objTransMat * objRotMat * objScaleMat;

}


/**
* Resets the orientation of the model.
*/
void Model::reset()
{
	this->objRotMat = glm::mat4(1);
	this->objTransMat = glm::mat4(1);
}

Model::~Model() {}

