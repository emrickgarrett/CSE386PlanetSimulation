#include "Controller.h"

class WaypointController : public Controller
{

public:
	WaypointController(vector<glm::vec3> waypoints, GLfloat speed);

	~WaypointController(void);

	virtual void update(float elapsedTimeSeconds);

	virtual GLfloat distanceToTargetWaypoint();

	virtual int getNextWaypointIndex();

	virtual void updateVelocityForWaypoint();

protected:
	vector<glm::vec3> waypoints;

	glm::vec3 position;

	int current;

	GLfloat speed;

	glm::vec3 velocity;
};

