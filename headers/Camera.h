#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 _position;
	glm::vec3 _rotationAngles = glm::vec3(0.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0);;

	void calculateViewMatrix();

public:
	Camera(const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0));
	glm::vec3 position();
	void setPosition(const glm::vec3& position);
	void rotate(const glm::vec3& rotationAngles);
	void rotate(const float& rotationX, const float& rotationY, const float& rotationZ);
	float rotationX();
	float rotationY();
	float rotationZ();
	glm::mat4 getViewMatrix();
};

