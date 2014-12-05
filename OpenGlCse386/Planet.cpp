#include "Planet.h"

#include "Sphere.h"
#include "VisualObject.h"
#include "time.h"
#include <math.h>
#include <string>

Planet::Planet(float r, int slices, int stacks, string soundLoc)
	: Sphere(r, slices,stacks){

		this -> soundLoc = soundLoc;
		this -> name = "default";
		srand(time(NULL));
}


Planet::~Planet(){
	Sphere::~Sphere();
}

void Planet::initialize(){
	Sphere::initialize();

	if(soundLoc.compare("default") == 0){
		determineSound();
		cout << " I am here..." << endl;
	}else{
		cout << "Strings are: " << soundLoc << endl;
	}

}

void Planet::draw(){
	Sphere::draw();
}

string Planet::getSound(){
	return this -> soundLoc;
}

void Planet::determineSound(){
	int randInt = rand()%7 + 1;

	this -> soundLoc = "sounds\\space" + std::to_string(randInt) + ".wav";

	cout << " I ended up with : " << soundLoc << endl;
}

void Planet::setName(string name){
	this -> name = name;
}

string Planet::getName(){
	return this -> name;
}

string Planet::getFacts(){
	string result = "default";

	if(name.compare("mercury") == 0){
		result = "Name: Mercury";
		result += "\nMass: 330,104,000,000,000 billion kg";
		result +="\nEarth Ratio: .055 x Earth";
		result +="\nEquatorial Diameter: 4,879km";
		result +="\nKnown Moons: None";
		result +="\nOrbit Distance: 57,909,227km";
		result +="\nOrbit Period: 87.97 Earth Days"; 
		result +="\nSurface Temperature: -173 to 427 °C";
	}
	if(name.compare("venus") == 0){
		result = "Name: Venus";
		result +="\nMass: 4,867,320,000,000,000 billion kg";
		result +="\nEarth Ratio: 0.815 x Earth";
		result +="\nEquatorial Diameter: 12,104 km";
		result +="\nKnown Moons: None";
		result +="\nOrbit Distance: 108,209,475 km";
		result +="\nOrbit Period: 224.70 Earth Days"; 
		result +="\nSurface Temperature: 462 °C";
	}
	if(name.compare("earth") == 0){
		result = "Name: Earth";
		result +="\nMass: 5,972,190,000,000,000 billion kg";
		result +="\nEarth Ratio: 1.00 x Earth";
		result +="\nEquatorial Diameter: 12,756 km";
		result +="\nKnown Moons: 1 (The Moon)";
		result +="\nOrbit Distance: 149,598,262 km";
		result +="\nOrbit Period: 365.26 Earth Days"; 
		result +="\nSurface Temperature: -88 to 58°C";
	}
	if(name.compare("mars") == 0){
		result = "Name: Mars";
		result +="\nMass: 641,693,000,000,000 billion kg";
		result +="\nEarth Ratio: 0.107 x Earth";
		result +="\nEquatorial Diameter: 6,805 km";
		result +="\nKnown Moons: 2 (Phobos & Deimos)";
		result +="\nOrbit Distance: 227,943,824 km";
		result +="\nOrbit Period: 686.98 Earth Days"; 
		result +="\nSurface Temperature: -87 to -5 °C";
	}
	if(name.compare("jupiter") == 0){
		result = "Name: Jupiter";
		result +="\nMass: 1,898,130,000,000,000,000 billion kg";
		result +="\nEarth Ratio: 317.83 x Earth";
		result +="\nEquatorial Diameter: 142,984 km";
		result +="\nKnown Moons: 67 (Io, Europa, Ganymede, & Callisto)";
		result +="\nOrbit Distance: 778,340,821 km";
		result +="\nOrbit Period: 4,332.82 Earth Days"; 
		result +="\nSurface Temperature: -108°C";
	}
	if(name.compare("saturn") == 0){
		result = "Name: Saturn";
		result +="\nMass: 568,319,000,000,000,000 billion kg";
		result +="\nEarth Ratio: 95.16 x Earth";
		result +="\nEquatorial Diameter: 120,536 km";
		result +="\nKnown Moons: 62 (Titan, Rhea, & Enceladus)";
		result +="\nOrbit Distance: 1,426,666,422 km";
		result +="\nOrbit Period: 10,755.70 Earth Days"; 
		result +="\nSurface Temperature: -139 °C";
	}
	if(name.compare("uranus") == 0){
		result = "Name: Uranus";
		result +="\nMass: 86,810,300,000,000,000 billion kg";
		result +="\nEarth Ratio: 14.536 x Earth";
		result +="\nEquatorial Diameter: 51,118 km";
		result +="\nKnown Moons: 27 (Oberon, Titania, Miranda, Ariel & Umbriel)";
		result +="\nOrbit Distance: 2,870,658,186 km";
		result +="\nOrbit Period: 30,687.15 Earth Days"; 
		result +="\nSurface Temperature: -197 °C";
	}
	if(name.compare("neptune") == 0){
		result = "Name: Neptune";
		result +="\nMass: 102,410,000,000,000,000 billion kg";
		result +="\nEarth Ratio: 17.15x Earth";
		result +="\nEquatorial Diameter: 49,528 km";
		result +="\nKnown Moons: 14 (Triton)";
		result +="\nOrbit Distance: 4,498,396,441 km";
		result +="\nOrbit Period: 60,190.03 Earth Days"; 
		result +="\nSurface Temperature: -201 °C";
	}
	if(name.compare("pluto") == 0){
		result = "Name: Pluto";
		result +="\nMass: 13,050,000,000,000 billion kg";
		result +="\nEarth Ratio: 0.00218 x Earth";
		result +="\nEquatorial Diameter: 2,368 km (+- 20km)";
		result +="\nKnown Moons: 5 (Charon, Nix, Hydra, Kerberos and Styx)";
		result +="\nOrbit Distance: 5,874,000,000 km";
		result +="\nOrbit Period: 246.04 Earth Days"; 
		result +="\nSurface Temperature: -229 °C";
	}
	if(name.compare("sun") == 0){
		result = "Name: Sun";
		result +="\nMass: 1,989,100,000,000,000,000,000 billion kg";
		result +="\nEarth Ratio: 333,060 x Earth";
		result +="\nEquatorial Diameter: 1,392,684 km";
		result +="\nSurface Temperature: 5500 °C";
	}
	return result;
}
