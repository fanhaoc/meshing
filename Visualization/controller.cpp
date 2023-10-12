#include "controller.h"
// 此页为全局变量

float lastX, lastY;
bool firstMouse = true;
Camera* camera; // 摄像机
	
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse == true) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
		return;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	camera->processMouseMovement(deltaX, deltaY);
}
