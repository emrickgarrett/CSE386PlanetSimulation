#include "Pyramid.h"
#include "Material.h"
#include "vertexStructs.h"
#include "textureCoordinates.h"

using namespace glm;

GLsizei numberOfIndices;
vector<pncVertexData> v;
vector<pntVertexData> norms;


void Pyramid::setShaderValues()
{
	// Bind the shader
    glUseProgram(shaderProgram);

	// Find the locations of the model matrix uniform variable in the shader
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);

	// Find the locations of the material properties in the Material struct called object
	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
							getUniformLocation( shaderProgram, "object.diffuseMat"),
							getUniformLocation( shaderProgram, "object.specularMat"),
							getUniformLocation( shaderProgram, "object.specularExp"),
							getUniformLocation( shaderProgram, "object.emissiveMat" ),
							getUniformLocation( shaderProgram, "object.textureMapped") );

}


/**
* Builds shader program and initializes vertex array object that will be used to render the 
* the object.
*/
void Pyramid::initialize()
{
	setShaderValues();

	GLuint VBO;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	vec3 v0 = vec3( (-width/2.0f), (-height/2.0f), (-width/2.0f) );
	vec3 v1 = vec3( (width/2.0f), (-height/2.0f), (-width/2.0f) );
	vec3 v2 = vec3( (width/2.0f), (-height/2.0f), (width/2.0f) );
	vec3 v3 = vec3( (-width/2.0f), (-height/2.0f), (width/2.0f) );
	vec3 v4 = vec3( 0.0f, (height/2.0f), 0.0f );

	// Front face
	vec3 frontFaceNormal = findUnitNormal(v4, v3, v2);
	vec4 frontFaceColor(1.0f, 0.0f, 0.0f, 1.0f);
	norms.push_back(pntVertexData(v4, frontFaceNormal, getPlanarTextCoords(v4, width, height)));
	norms.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));
	norms.push_back(pntVertexData(v2, frontFaceNormal, getPlanarTextCoords(v2, width, height)));

	// Right face
	vec3 rightFaceNormal = findUnitNormal(v4, v2, v1);
	vec4 rightFaceColor(1.0f, 0.0f, 0.0f, 1.0f);
	norms.push_back(pntVertexData(v4, rightFaceNormal, getPlanarTextCoords(v4, width, height)));
	norms.push_back(pntVertexData(v2, rightFaceNormal, getPlanarTextCoords(v2, width, height)));
	norms.push_back(pntVertexData(v1, rightFaceNormal, getPlanarTextCoords(v1, width, height)));

	// Left face
	vec3 leftFaceNormal = findUnitNormal(v4, v0, v3);
	vec4 leftFaceColor(1.0f, 0.0f, 0.0f, 1.0f);
	norms.push_back(pntVertexData(v4, leftFaceNormal, getPlanarTextCoords(v4, width, height)));
	norms.push_back(pntVertexData(v0, leftFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v3, leftFaceNormal, getPlanarTextCoords(v3, width, height)));

	// Back face
	vec3 backFaceNormal = findUnitNormal(v4, v1, v0);
	vec4 backFaceColor(1.0f, 0.0f, 0.0f, 1.0f);
	norms.push_back(pntVertexData(v4, backFaceNormal, getPlanarTextCoords(v4, width, height)));
	norms.push_back(pntVertexData(v1, backFaceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v0, backFaceNormal, getPlanarTextCoords(v0, width, height)));

	// Bottom face
	vec3 bottomFaceNormal = vec3(0.0f, -1.0f, 0.0f);
	vec4 bottomFaceColor(1.0f, 0.0f, 0.0f, 1.0f);
	norms.push_back(pntVertexData(v1, bottomFaceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v3, bottomFaceNormal, getPlanarTextCoords(v3, width, height)));
	norms.push_back(pntVertexData(v0, bottomFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v2, bottomFaceNormal, getPlanarTextCoords(v2, width, height)));
	norms.push_back(pntVertexData(v3, bottomFaceNormal, getPlanarTextCoords(v3, width, height)));
	norms.push_back(pntVertexData(v1, bottomFaceNormal, getPlanarTextCoords(v1, width, height)));

	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO);
	glBufferData( GL_ARRAY_BUFFER, norms.size() * sizeof(pntVertexData), &norms[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*) sizeof(vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)( sizeof(vec3) * 2));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);
	
	// Initialize all children
	VisualObject::initialize();

} // end initialize

/*
* Renders the object using the visual object using the vertex array object that was created by
* the initialize method.
*/
void Pyramid::draw()
{
	glUseProgram(shaderProgram);

	glBindVertexArray(vertexArrayObject);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));

	material.setShaderMaterialProperties();

	glDrawArrays( GL_TRIANGLES, 0, norms.size());
	//glDrawElements( GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0 );

	// Draw all children
	VisualObject::draw();

} // end draw


/**
* Constructor for the Pyramid class. Created a visual object in the shape of a pyramid. Vertex
* positions are expressed relative to an origin that is located in the center of the pyramid.
* @param OpenGLApp - reference to the OpenGLApplicationBase object that holds the projection
*        and viewing transformations
* @param w - width of the base of the pyramid. Default is 1 unit.
* @param h - height of the pyramid. Default is 1 unit.
*/
Pyramid::Pyramid( GLfloat w, GLfloat h)
{
	width = w;
	height = h;
} // end constructor
