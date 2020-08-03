#include "includes/Shader.hpp"

int Shader::light = 0;
int Shader::texture= 0;
int Shader::textureLight = 0;
int Shader::passthrough = 0;
int Shader::shadow = 0;
int Shader::skybox = 0;
int Shader::terrain = 0;

int Shader::compileShader(const char * path, int shaderType)
{
	std::ifstream file;
	file.open(path, std::ios::in);
	if (!file.is_open()) {
		std::cout << "Failed to open shader : " << path << std::endl;
		return -1;
	}

	std::string contents;
	std::string line = "";
	while (!file.eof()) {
		std::getline(file, line);
		contents.append(line + "\n");
	}

	file.close();

	const char * source = contents.c_str();
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cerr << "Compilation failed for " << path << "\n" << infoLog << std::endl;
		return -1;
	}

	return shaderId;
}

int Shader::compileAndLinkShaders(const char * vertexPath, const char * fragmentPath)
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------

	// vertex shader
	int vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);

	if (vertexShader == -1)
		exit(EXIT_FAILURE);

	int fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

	if (fragmentShader == -1)
		exit(EXIT_FAILURE);

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

Shader::Shader() {
	Shader::light = compileAndLinkShaders("../Shaders/phong.vshader", "../Shaders/phong.fshader");
	Shader::texture = compileAndLinkShaders("../Shaders/texture.vshader", "../Shaders/texture.fshader");
	Shader::textureLight = compileAndLinkShaders("../Shaders/textureLight.vshader", "../Shaders/textureLight.fshader");
	Shader::passthrough = compileAndLinkShaders("../Shaders/passthrough.vshader", "../Shaders/passthrough.fshader");
	Shader::shadow = compileAndLinkShaders("../Shaders/shadow.vshader", "../Shaders/shadow.fshader");
	Shader::skybox = compileAndLinkShaders("../Shaders/skybox.vshader", "../Shaders/skybox.fshader");
	Shader::terrain = compileAndLinkShaders("../Shaders/terrain.vshader", "../Shaders/terrain.fshader");
}