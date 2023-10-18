#include "controller.h"
// 此页为全局变量

bool isRotate = false;
float lastX, lastY;
float rotateSense = 0.1f; // 相机转动的灵敏度
bool firstMouse = true;

float fov = 45.0f;
float maxFov = 75.0f;
float minFov = 1.0f;
float fovSense = 100.0f;

float moveSense = 0.05f;

Camera* camera; // 摄像机
	
void null_callback(GLFWwindow* window, double xPos, double yPos) {}

void rotate_callback(GLFWwindow* window, double xPos, double yPos) {
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

	camera->processMouseMovement(deltaX * rotateSense, deltaY * rotateSense);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= minFov && fov <= maxFov) {
		fov -= yoffset;
	}
	if (fov <= minFov) {
		fov = minFov;
	}
	if (fov >= maxFov) {
		fov = maxFov;
	}
}

void move_callback(GLFWwindow* window, double xPos, double yPos){

}

// 鼠标按钮输入事件
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if(button == GLFW_MOUSE_BUTTON_LEFT) 
			glfwSetCursorPosCallback(window, rotate_callback);
		if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			glfwSetCursorPosCallback(window, move_callback);
	}
	if (action == GLFW_RELEASE) {
		glfwSetCursorPosCallback(window, null_callback);
		firstMouse = true;
	}
	//glfwSetCursorPosCallback(window, mouse_callback);
}

// 键盘输入处理函数
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// wasd移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->Position += glm::normalize(camera->Forward) * moveSense;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->Position -= glm::normalize(camera->Forward) * moveSense; 
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->Position += glm::normalize(camera->Right) * moveSense;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->Position -= glm::normalize(camera->Right) * moveSense;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera->Position -= glm::normalize(camera->Up) * moveSense;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera->Position += glm::normalize(camera->Up) * moveSense;
	}
}