#pragma once
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

// ��ҳΪȫ�ֱ���

extern float lastX, lastY;
extern bool firstMouse;
extern Camera* camera; // �����

extern void mouse_callback(GLFWwindow* window, double xPos, double yPos);