#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ImportedModel.h"
#include "Texture.h"

class GameObject
{
private:
	ImportedModel* model;
	Texture* texture;
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::mat4 modelMatrix = glm::mat4(1.0);

	void calculateModelMatrix();

public:
	GameObject(ImportedModel& model, Texture& texture);
	GLuint getTextureID();
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	ImportedModel* getModel();
	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	void setScale(float scale);
	void setRotation(const glm::vec3& rotation);
	void setModel(ImportedModel& model);
	glm::mat4 getModelMatrix();
};

