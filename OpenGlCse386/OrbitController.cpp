#include "OrbitController.h"


OrbitController::OrbitController(glm::vec3 pos, glm::vec3 rax, glm::vec3 oax, GLfloat r) : rotation(0.0f)
{
	position = pos;

	rotationAxis = rax;

	orbitAxis = oax;

	rate = r;
}

void OrbitController::update(float elapsedTimeSeconds)
{
	rotation += elapsedTimeSeconds * rate;

	target->modelMatrix = glm::rotate(glm::mat4(1.0f), fmod(rotation, 360.0f), orbitAxis) * glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), fmod(rotation, 360.0f), rotationAxis);
}


OrbitController::~OrbitController(void)
{
}
