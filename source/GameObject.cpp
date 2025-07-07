#include "GameObject.h"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL2/SOIL2.h>
#include <iostream>

using namespace std;

GameObject::GameObject(ImportedModel& model, Texture& texture)
{
	this->model = &model;
	this->texture = &texture;

	calculateModelMatrix();
}

GLuint GameObject::getTextureID()
{
	return texture->getTextureId();
}

glm::vec3 GameObject::getPosition()
{
	return position;
}

glm::vec3 GameObject::getRotation()
{
	return rotation;
}

glm::vec3 GameObject::getScale()
{
	return scale;
}

ImportedModel* GameObject::getModel()
{
	return model;
}

void GameObject::setPosition(const glm::vec3& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;

	calculateModelMatrix();
}

void GameObject::setScale(const glm::vec3& scale)
{
	this->scale.x = scale.x;
	this->scale.y = scale.y;
	this->scale.z = scale.z;

	calculateModelMatrix();
}

void GameObject::setScale(float scale)
{
	this->scale.x = scale;
	this->scale.y = scale;
	this->scale.z = scale;

	calculateModelMatrix();
}

void GameObject::setRotation(const glm::vec3& rotation)
{
	this->rotation.x = (float)fmod(rotation.x, 360);
	this->rotation.y = (float)fmod(rotation.y, 360);
	this->rotation.z = (float)fmod(rotation.z, 360);

	calculateModelMatrix();
}

void GameObject::setModel(ImportedModel& model)
{
	this->model = &model;
}

void GameObject::calculateModelMatrix()
{
	modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)), scale);
}

glm::mat4 GameObject::getModelMatrix() {
	return modelMatrix;
}
