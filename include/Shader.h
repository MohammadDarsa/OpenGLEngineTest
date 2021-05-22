#ifndef SHADER_H
#define SHADER_H

#include<glad\glad.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<string>
#include<fstream>
#include<sstream>
#include<Light.h>
#include<iostream>

class Shader {
public:
	//Program ID
	unsigned int ID;

	//constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//use/activate the shader
	void use();
	//utility uniform functions
	void setBool(const char name[], bool value) const;
	void setInt(const char name[], int value) const;
	void setFloat(const char name[], float value) const;
	void setMat4(const char name[], glm::mat4 &matrix) const;
	void setVec3(const char name[], glm::vec3 vec) const;
	void setVec3(const char name[], float x, float y, float z) const;
	void setPointLight(const PointLight &light, int i) const;
	void setSpotLight(const SpotLight& light, int i) const;
	void setDirectionalLight(const DirectionalLight& light, int i) const;
	
	

	~Shader();

};

#endif