#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Shader {
public:
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; // shader program ID
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	//~Shader();
private:
	void checkCompileErrors(unsigned int  ID, std::string type);
};
