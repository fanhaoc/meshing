#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
public:
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; // shader program ID

	enum Slot
	{
		DIFFUSE,
		SPECULAR,
		EMISSION
	};

	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setUniform3f(const char* paramNameString, glm::vec3 param);
	void setUniform1f(const char* paramNameString, float param);
	void setUniform1i(const char* paramNameString, unsigned int slot);
	//~Shader();
private:
	void checkCompileErrors(unsigned int  ID, std::string type);
};
