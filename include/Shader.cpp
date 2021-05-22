#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file�s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//print if linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const char name[], bool value) const {
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setInt(const char name[], int value) const {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const char name[], float value) const {
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setMat4(const char name[], glm::mat4 &matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const char name[], glm::vec3 vec) const {
	glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
}
void Shader::setVec3(const char name[], float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::setPointLight(const PointLight& light, int i) const {
	std::string str = "pointLights[" + std::to_string(i) + "].";
	setVec3((str + "position").c_str(), light.position);
	setVec3((str + "ambient").c_str(), light.ambient);
	setVec3((str + "diffuse").c_str(), light.diffuse);
	setVec3((str + "specular").c_str(), light.specular);
	setFloat((str + "constant").c_str(), light.constant);
	setFloat((str + "linear").c_str(), light.linear);
	setFloat((str + "quadratic").c_str(), light.quadratic);
}
void Shader::setSpotLight(const SpotLight& light, int i) const {
	std::string str = "spotLights[" + std::to_string(i) + "].";
	setVec3((str + "position").c_str(), light.position);
	setVec3((str + "direction").c_str(), light.direction);
	setVec3((str + "ambient").c_str(), light.ambient);
	setVec3((str + "diffuse").c_str(), light.diffuse);
	setVec3((str + "specular").c_str(), light.specular);
	setFloat((str + "constant").c_str(), light.constant);
	setFloat((str + "linear").c_str(), light.linear);
	setFloat((str + "quadratic").c_str(), light.quadratic);
	setFloat((str + "innerCutOff").c_str(), light.innerCutOff);
	setFloat((str + "outerCutOff").c_str(), light.outerCutOff);
}
void Shader::setDirectionalLight(const DirectionalLight& light, int i) const {
	std::string str = "directionalLights[" + std::to_string(i) + "].";
	setVec3((str + "direction").c_str(), light.direction);
	setVec3((str + "ambient").c_str(), light.ambient);
	setVec3((str + "diffuse").c_str(), light.diffuse);
	setVec3((str + "specular").c_str(), light.specular);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}



