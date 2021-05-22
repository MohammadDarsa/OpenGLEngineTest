#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct PointLight {
	glm::vec3 position{ glm::vec3(0.0f) };
	glm::vec3 ambient{ glm::vec3(0.5f) };
	glm::vec3 diffuse{ glm::vec3(1.0f) };
	glm::vec3 specular{ glm::vec3(1.0f) };

	float constant{ 1.0f };
	float linear{ 0.09f };
	float quadratic{ 0.032f };


	PointLight() {};
	PointLight(glm::vec3 position) :position(position) {};
	PointLight(float x, float y, float z) :position(glm::vec3(x, y, z)) {};
	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) :position(position), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadratic(quadratic) {};
};

struct DirectionalLight {
	glm::vec3 direction{ glm::vec3(1.0f) };
	glm::vec3 ambient{ glm::vec3(0.1f) };
	glm::vec3 diffuse{ glm::vec3(0.8f) };
	glm::vec3 specular{ glm::vec3(1.0f) };

	DirectionalLight() {};
	DirectionalLight(glm::vec3 direction) :direction(direction) {};
	DirectionalLight(float x, float y, float z) :direction(glm::vec3(x, y, z)) {};
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {};
};

struct SpotLight {
	glm::vec3 position{ glm::vec3(0.0f) };
	glm::vec3 direction{ glm::vec3(1.0f) };
	glm::vec3 ambient{ glm::vec3(0.0f) };
	glm::vec3 diffuse{ glm::vec3(1.0f) };
	glm::vec3 specular{ glm::vec3(1.0f) };

	float constant{ 1.0f };
	float linear{ 0.09f };
	float quadratic{ 0.032f };
	float innerCutOff{ glm::cos(glm::radians(15.0f)) };
	float outerCutOff{ glm::cos(glm::radians(17.5f)) };

	SpotLight() {};
	SpotLight(glm::vec3 position, glm::vec3 direction) :position(position), direction(direction) {};
	SpotLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float innerCutOff, float outerCutOff) :position(position), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadratic(quadratic), innerCutOff(innerCutOff), outerCutOff(outerCutOff) {};
};
