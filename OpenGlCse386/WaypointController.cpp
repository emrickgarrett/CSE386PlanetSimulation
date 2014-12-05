#include "WaypointController.h"


WaypointController::WaypointController(vector<glm::vec3> waypoints, GLfloat speed)
{
	this->waypoints = waypoints;

	this->position = waypoints[0];

	this->current = 1;

	this->speed = speed;

	updateVelocityForWaypoint();
}

void WaypointController::update(float elapsedTimeSeconds)
{
	if ( distanceToTargetWaypoint() < (speed * elapsedTimeSeconds) ) {
		position = waypoints[current];
		getNextWaypointIndex();

		updateVelocityForWaypoint();
	}

	position = position + velocity * elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);

} // end update

GLfloat WaypointController::distanceToTargetWaypoint() {
	return glm::distance(position, waypoints.at(current));
} // end distanceToTargetWaypoint

int WaypointController::getNextWaypointIndex() {
	current = (current+1) % waypoints.size();

	return current;
} // end getNextWaypointIndex

void WaypointController::updateVelocityForWaypoint() {
	velocity = speed * glm::normalize(waypoints.at(current) - position);
} // end updateVelocityForWaypoint



WaypointController::~WaypointController(void)
{
}
