#include "Controller.h"

class SpinnerController : public Controller
{

public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	SpinnerController( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3 ax = glm::vec3(1.0, 0.0f, 0.0f), GLfloat r = 10.0f);

	~SpinnerController();
	
	virtual void update(float elapsedTimeSeconds);

protected:

	// Position at which the object is spinning in place
	glm::vec3 position;

	// axis of rotation
	glm::vec3 axis;

	// rate and direction of rotation
	GLfloat rate;

	float rotation;
};
