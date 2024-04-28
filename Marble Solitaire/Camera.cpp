#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& rotation) {
	this->_position = glm::vec3(-position.x, -position.y, -position.z);
	this->_rotationAngles = glm::vec3(fmod(rotation.x, 360), fmod(rotation.y, 360), fmod(rotation.z, 360));

	calculateViewMatrix();
}
glm::vec3 Camera::position() {
	return this->_position;
}
void Camera::setPosition(const glm::vec3& position) {
	this->_position = position;

	calculateViewMatrix();
}
void Camera::rotate(const glm::vec3& rotationAngles) {
	this->_rotationAngles.x = rotationAngles.x;
	this->_rotationAngles.y = rotationAngles.y;
	this->_rotationAngles.z = rotationAngles.z;

	calculateViewMatrix();
}
void Camera::rotate(const float& rotationX, const float& rotationY, const float& rotationZ) {
	this->_rotationAngles.x = rotationX;
	this->_rotationAngles.y = rotationY;
	this->_rotationAngles.z = rotationZ;

	calculateViewMatrix();
}
float Camera::rotationX() {
	return this->_rotationAngles.x;
}
float Camera::rotationY() {
	return this->_rotationAngles.y;
}
float Camera::rotationZ() {
	return this->_rotationAngles.z;
}
void Camera::calculateViewMatrix() {
	viewMatrix = glm::translate(glm::mat4(1.0f), this->_position) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotationX()), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotationY()), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
}
glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}