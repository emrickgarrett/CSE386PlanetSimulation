#ifndef ___PLANET_H___
#define ___PLANET_H___

#include "visualobject.h"
#include "Sphere.h"

class Planet : public Sphere
{
	public:
		Planet(float Radius = 1.0f, int slices = 16, int stacks = 16, string soundLoc  = "default");
		~Planet(void);

		virtual void initialize();

		virtual void draw();

		virtual string getSound();

		virtual string getName();

		virtual void setName(string name);

		virtual string getFacts();

	protected:
		string soundLoc;
		string name;

		virtual void determineSound();
};

#endif // ___SPACESHIP_H___