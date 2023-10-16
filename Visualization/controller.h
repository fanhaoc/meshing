#pragma once
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

// 此页为全局变量
extern bool isRotate; // 是否开启旋转
extern float lastX, lastY;
extern bool firstMouse;
// 视角缩放
extern float fov;
extern float maxFov;
extern float minFov;
extern float fovSense;

extern float moveSense;
extern Camera* camera; // 摄像机

extern void null_callback(GLFWwindow* window, double xPos, double yPos);

extern void rotate_callback(GLFWwindow* window, double xPos, double yPos);

extern void move_callback(GLFWwindow* window, double xPos, double yPos);

void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

extern void processInput(GLFWwindow* window);