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
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::processMouseMovement(float deltaX, float deltaY) {
	Pitch += deltaY;
	Yaw += deltaX;
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}