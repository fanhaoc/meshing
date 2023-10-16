#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
	Position = position;
	WorldUp = worldUp;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp) {
	Position = position;
	WorldUp = worldUp;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
	Forward.y = glm::sin(glm::radians(Pitch));
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::processMouseMovement(float deltaX, float deltaY) {
	Pitch += deltaY;
	Yaw += deltaX;
	if (Pitch > 89.0f) {
		Pitch = 89.0f;
	}
	if (Pitch < -89.0f) {
		Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
	Forward.y = glm::sin(glm::radians(Pitch));
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}