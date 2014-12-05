#include "Controller.h"

class OrbitController : public Controller
{

public:
	OrbitController(glm::vec3 pos, glm::vec3 rax, glm::vec3 oax, GLfloat r);
	
	~OrbitController(void);

	virtual void update(float elapsedTimeSeconds);

protected:

	// Position at which the object is spinning in place
	glm::vec3 position;

	// axis of rotation
	glm::vec3 rotationAxis;

	// axis of orbit
	glm::vec3 orbitAxis;

	// rate and direction of rotation
	GLfloat rate;

	float rotation;
};

