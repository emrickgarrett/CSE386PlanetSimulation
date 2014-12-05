#include "OpenGLApplicationBase.h"
#include "glutBase.h"
#include "Floor.h"
#include "Pyramid.h"
#include "Controller.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "Material.h"
#include "Floor2.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "SharedGeneralLighting.h"
#include "SpaceShip.h"
#include "Wall.h"
#include "Planet.h"
#include "font.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <mmsystem.h>

class finalProject : public OpenGLApplicationBase
{
public:
	Material material;
	
	Planet* sun;
	Planet* mercury;
	Planet* venus;
	Planet* earth;
	Planet* mars;
	Planet* jupiter;
	Planet* saturn;
	Planet* uranus;
	Planet* neptune;
	Planet* pluto;

	Planet* activePlanet;

	GLint view;
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat z;
	SharedGeneralLighting generalLighting;

	finalProject ()
	{
		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag" },
			{ GL_NONE, NULL } // signals that there are no more shaders
		};

		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);

		view = 0;
		rotationX = 0;
		rotationY = 0;
		z = -15.0f;

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader(shaderProgram);

		sun = new Planet(3.0f);
		sun -> setName("sun");
		sun->setShader(shaderProgram);
		sun->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		sun->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		sun->material.setTextureMapped(true);
		sun->material.setupTexture("sunmap.bmp");
		addChild(sun);

		mercury = new Planet(0.25f);
		mercury -> setName("mercury");
		mercury->setShader(shaderProgram);
		mercury->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		mercury->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		mercury->material.setTextureMapped(true);
		mercury->material.setupTexture("mercurymap.bmp");
		addChild(mercury);

		venus = new Planet(0.5f);
		venus -> setName("venus");
		venus->setShader(shaderProgram);
		venus->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		venus->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		venus->material.setTextureMapped(true);
		venus->material.setupTexture("venusmap.bmp");
		addChild(venus);

		earth = new Planet(0.5f);
		earth -> setName("earth");
		earth->setShader(shaderProgram);
		earth->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		earth->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		earth->material.setTextureMapped(true);
		earth->material.setupTexture("earthmap.bmp");
		addChild(earth);

		mars = new Planet(0.33f);
		mars -> setName("mars");
		mars->setShader(shaderProgram);
		mars->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		mars->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		mars->material.setTextureMapped(true);
		mars->material.setupTexture("marsmap.bmp");
		addChild(mars);

		jupiter = new Planet(1.75f);
		jupiter -> setName("jupiter");
		jupiter->setShader(shaderProgram);
		jupiter->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		jupiter->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		jupiter->material.setTextureMapped(true);
		jupiter->material.setupTexture("jupitermap.bmp");
		addChild(jupiter);

		saturn = new Planet(1.7f);
		saturn -> setName("saturn");
		saturn->setShader(shaderProgram);
		saturn->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		saturn->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		saturn->material.setTextureMapped(true);
		saturn->material.setupTexture("saturnmap.bmp");
		addChild(saturn);

		uranus = new Planet(1.0f);
		uranus -> setName("uranus");
		uranus->setShader(shaderProgram);
		uranus->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		uranus->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		uranus->material.setTextureMapped(true);
		uranus->material.setupTexture("uranusmap.bmp");
		addChild(uranus);

		neptune = new Planet(1.0f);
		neptune -> setName("neptune");
		neptune->setShader(shaderProgram);
		neptune->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		neptune->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		neptune->material.setTextureMapped(true);
		neptune->material.setupTexture("neptunemap.bmp");
		addChild(neptune);

		pluto = new Planet(0.25f);
		pluto -> setName("pluto");
		pluto->setShader(shaderProgram);
		pluto->fixedTransformation = rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		pluto->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		pluto->material.setTextureMapped(true);
		pluto->material.setupTexture("plutomap.bmp");
		addChild(pluto);

		sun->addController( new SpinnerController(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 25.0f) );
		mercury->addController( new OrbitController(vec3(4.5f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 25.0f) );
		venus->addController( new OrbitController(vec3(7.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 18.0f) );
		earth->addController( new OrbitController(vec3(11.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 15.0f) );
		mars->addController( new OrbitController(vec3(15.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 15.0f) );
		jupiter->addController( new OrbitController(vec3(25.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 11.0f) );
		saturn->addController( new OrbitController(vec3(35.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 11.0f) );
		uranus->addController( new OrbitController(vec3(45.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 9.0f) );
		neptune->addController( new OrbitController(vec3(50.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 7.0f) );
		pluto->addController( new OrbitController(vec3(55.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 5.0f) );

		setupLighting(shaderProgram);

	}

	void setupLighting(GLuint shaderProgram)
	{
		// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true );
		generalLighting.setAmbientColor( GL_LIGHT_ZERO, vec4(0.8f, 0.8f, 0.8f, 1.0f) );

		//// ***** Directional Light **************
		//generalLighting.setEnabled( GL_LIGHT_ONE, true );
		//generalLighting.setDiffuseColor( GL_LIGHT_ONE, vec4(0.75f, 0.75f, 0.75f, 1.0f) );
		//generalLighting.setSpecularColor( GL_LIGHT_ONE, vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		//generalLighting.setPositionOrDirection( GL_LIGHT_ONE, vec4(1.0f, 1.0f, 1.0f, 0.0f) );

		// ***** Positional Light **************
		generalLighting.setEnabled( GL_LIGHT_TWO, true );
		generalLighting.setDiffuseColor( GL_LIGHT_TWO, vec4(0.5f, 0.5f, 0.5f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_TWO, vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_TWO, vec4(0.0f, 0.0f, 0.0f, 1.0f) );

		//// ***** Spot Light **************
		//generalLighting.setEnabled( GL_LIGHT_THREE, true );
		//generalLighting.setIsSpot( GL_LIGHT_THREE, true );
		//generalLighting.setDiffuseColor( GL_LIGHT_THREE, vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		//generalLighting.setSpecularColor( GL_LIGHT_THREE, vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		//generalLighting.setPositionOrDirection( GL_LIGHT_THREE, vec4(0.0f, 8.0f, 0.0f, 1.0f) );
		//generalLighting.setSpotDirection( GL_LIGHT_THREE, vec3(0.0f, -1.0f, 0.0f) );
		//generalLighting.setSpotCutoffCos( GL_LIGHT_THREE, cos(glm::radians(15.0f)) );
		
	} // end setUpLighting

	virtual void initialize()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glutSpecialFunc(SpecialKeyboardCB);

		setUpMenus();

		//floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));

		sun->modelMatrix = mat4(1.0f);
		mercury->modelMatrix = mat4(1.0f);
		venus->modelMatrix = mat4(1.0f);
		earth->modelMatrix = mat4(1.0f);
		mars->modelMatrix = mat4(1.0f);
		jupiter->modelMatrix = mat4(1.0f);
		saturn->modelMatrix = mat4(1.0f);
		uranus->modelMatrix = mat4(1.0f);
		neptune->modelMatrix = mat4(1.0f);
		pluto->modelMatrix = mat4(1.0f);
		activePlanet = NULL;

		VisualObject::initialize();

		playSound("sounds\\space_oddity.wav");
	} // end initialize



	// Update scene objects in between frames
	virtual void update( float elapsedTimeSec )
	{
		setViewPoint( );

		static float rotation = 0.0f;

		rotation += elapsedTimeSec * 25.0f;

		VisualObject::update(elapsedTimeSec);

	} // end update

	virtual void draw(){
		if(activePlanet != NULL){
			showFacts(activePlanet -> getFacts());
		}

		VisualObject::draw();
	}

	void setViewPoint( )
	{
		glm::mat4 viewMatrix;
		glm::mat4 rotateViewY;
		glm::mat4 rotateViewX;
		glm::mat4 transView;
		switch (view) {
			case 0:
				viewMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -15));

				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 1:
				viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, -10));

				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 2:
				viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(  0.0f, 0.0f, -10)) * glm::rotate(glm::mat4(1.0f), fmod(45.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 3:
				viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -12)) * glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				
				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 4:
				viewMatrix = glm::lookAt( glm::vec3( 0.0f, 0.0f, 10 ),
										  glm::vec3( 0.0f, 0.0f, 0.0f ),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 5:
				viewMatrix = glm::lookAt( glm::vec3( 0.0f, 7.07f, 7.07f ),
										  glm::vec3( 0.0f, 0.0f, 0.0f ),
										  glm::vec3( 0.0f, 7.07f, -7.07f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 6:
				viewMatrix = glm::lookAt( glm::vec3( 0.0f, 12, 0.0f ),
										  glm::vec3( 0.0f, 0.0f, 0.0f ),
										  glm::vec3( 1.0f, 0.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);

				break;
			case 7:
				transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, z ));
				rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
				rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));

				projectionAndViewing.setViewMatrix( transView * rotateViewX * rotateViewY );
				break;
			case 8://Sun
				viewMatrix = glm::lookAt( sun -> getWorldPosition() - glm::vec3( 12.0f, 0.0f, 0.0f ),
										  sun -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 9://Mercury
				viewMatrix = glm::lookAt( mercury -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  mercury -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 10://Venus
				viewMatrix = glm::lookAt( venus -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  venus -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 11://Earth
				viewMatrix = glm::lookAt( earth -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  earth -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 12://Mars
				viewMatrix = glm::lookAt( mars -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  mars -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 13://Jupiter
				viewMatrix = glm::lookAt( jupiter -> getWorldPosition() - glm::vec3( 7.0f, 0.0f, 0.0f ),
										  jupiter -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 14://Saturn
				viewMatrix = glm::lookAt( saturn -> getWorldPosition() - glm::vec3( 7.0f, 0.0f, 0.0f ),
										  saturn -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 15://Uranus
				viewMatrix = glm::lookAt( uranus -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  uranus -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 16://Neptune
				viewMatrix = glm::lookAt( neptune -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  neptune -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
			case 17://Pluto
				viewMatrix = glm::lookAt( pluto -> getWorldPosition() - glm::vec3( 3.0f, 0.0f, 0.0f ),
										  pluto -> getWorldPosition(),
										  glm::vec3( 0.0f, 1.0f, 0.0f ));
				
				projectionAndViewing.setViewMatrix(viewMatrix);
				break;
		}

		if(view < 8 || view > 17){
			activePlanet = NULL;
		}

	} // end setViewPoint

	void KeyboardCB(unsigned char Key, int x, int y)
	{
		bool lightOn;

		switch (Key) {
		case 'w':
			z++;
			break;
		case 's':
			z--;
			break;
		case 'a':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );
			break;
		case 'd':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ONE );
			generalLighting.setEnabled( GL_LIGHT_ONE, !lightOn );
			break;
		case 'p':
			lightOn = generalLighting.getEnabled( GL_LIGHT_TWO );
			generalLighting.setEnabled( GL_LIGHT_TWO, !lightOn );
			break;
		case 'l':
			lightOn = generalLighting.getEnabled( GL_LIGHT_THREE );
			generalLighting.setEnabled( GL_LIGHT_THREE, !lightOn );
			break;
		case '1'://Sun
			
			view = 1 + 7;
			activePlanet = sun;
			break;
		case '2'://Mercury

			view = 2 + 7;
			activePlanet = mercury;
			break;
		case '3'://Venus

			view = 3 + 7;
			activePlanet = venus;
			break;
		case '4'://earth

			view = 4 + 7;
			activePlanet = earth;
			break;
		case '5'://mars

			view = 5 + 7;
			activePlanet = mars;
			break;
		case '6'://jupiter

			view = 6 + 7;
			activePlanet = jupiter;
			break;
		case '7'://saturn

			view = 7 + 7;
			activePlanet = saturn;
			break;
		case '8'://uranus

			view = 8 + 7;
			activePlanet = uranus;
			break;
		case '9'://neptune

			view = 9 + 7;
			activePlanet = neptune;
			break;
		case '0'://pluto

			view = 10+ 7;
			activePlanet = pluto;
			break;
		case 'P':
			playSound("sounds\\space_oddity.wav");
			break;
		case 'z'://Play Planets Sound
			if(activePlanet != NULL)
				playSound(activePlanet -> getSound());
			break;
		default:
			OpenGLApplicationBase::KeyboardCB(Key, x, y);
			break;
		}
	} // end KeyboardCB

	void showFacts(string facts){
		screenTextOutput(20,200, facts);
	}

	friend void viewMenu(int value);

	friend void SpecialKeyboardCB(int Key, int x, int y);

	friend void playSound(string sound);

protected:
	GLuint createViewMenu()
	{
		GLuint menuId = glutCreateMenu(viewMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("View 1", 1);
		glutAddMenuEntry("View 2", 2);
		glutAddMenuEntry("View 3", 3);
		glutAddMenuEntry("View 4", 4);
		glutAddMenuEntry("View 5", 5);
		glutAddMenuEntry("View 6", 6);
		glutAddMenuEntry("View 7", 7);

		return menuId;
	} // end createFigureMenu

	void setUpMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createViewMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasingMenu();
		
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id); // Attach polygon Menu
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Rendered Polygon Face ", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti Aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

	} // end setUpMenus

}; // end stilgekiLab8


finalProject* classPtr;

static void SpecialKeyboardCB(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		classPtr->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		classPtr->rotationY++;
		break;
	case GLUT_KEY_UP:
		classPtr->rotationX++;
		break;
	case GLUT_KEY_DOWN:
		classPtr->rotationX--;
		break;
	default:
		
		break;
	}
} // end SpecialKeyboardCB

void viewMenu (int value)
{
	classPtr-> view = value;
	cout << "View point " << value << endl;

} // end viewMenu

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);

	GLUTBaseCreateWindow( "CSE 386 Final Project" );

	finalProject pApp;

	classPtr = &pApp;

	GLUTBaseRunApplication(&pApp);

} // end main

std::wstring convertStringToWString(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void playSound(string sound){
	PlaySound(convertStringToWString(sound).c_str(), NULL, SND_FILENAME | SND_ASYNC);
}