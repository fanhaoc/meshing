#pragma once
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

// 此页为全局变量

extern float lastX, lastY;
extern bool firstMouse;
extern Camera* camera; // 摄像机

extern void mouse_callback(GLFWwindow* window, double xPos, double yPos);