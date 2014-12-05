// Specifying version of GLSL. If the compiler does not support 
// this version of higher, an error will occur.
#version 330

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings (but can cause an error on some machines)
precision mediump float;

// Structure for holding general light properties
struct GeneralLight {
  
	vec4 ambientColor;		// ambient color of the light
	vec4 diffuseColor;		// diffuse color of the light
    vec4 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
    vec4 positionOrDirection;    
					  
	// spotlight attributes
    vec3 spotDirection;		// the direction the cone of light is shinning    
	int isSpot;				// 1 if the light is a spotlight  
    float spotCutoffCos;	// Cosine of the spot cutoff angle
    float spotExponent;		// For gradual falloff near cone edge

	// attenuation coefficients
    float constant; 
    float linear;
    float quadratic;

	int enabled;			// 1 if light is "on"

};

// Structure for material properties
struct Material
{
	vec4 ambientMat;

	vec4 diffuseMat;

	vec4 specularMat;

	float specularExp;

	vec4 emissiveMat;

	bool textureMapped;
};

const int MaxLights = 8;

layout (std140) uniform LightBlock
{
 GeneralLight lights[MaxLights];
};


uniform Material object;

// Sampler to determine interpolated texture coordinates for the fragment
uniform sampler2D gSampler;

layout (std140) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

// Vertex attributes passed in by the vertex shader
in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;  

// Output color for the fragment (pixel)
out vec4 FragColor;

vec4 calcLight( GeneralLight light, Material object )
{
	vec4 totalLight = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	
	vec4 ambientTerm = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	vec4 directionalTerm = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	vec4 positionalTerm = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	vec4 spotTerm = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	
	if (light.enabled == 1) {
		ambientTerm = object.ambientMat * light.ambientColor;
		totalLight += ambientTerm;

		if (light.positionOrDirection.w == 0.0f) {
			// Diffuse
			float diffuseFactor = max(dot(Normal0, light.positionOrDirection.xyz), 0.0f);
			directionalTerm = diffuseFactor * object.diffuseMat * light.diffuseColor;
			
			// Specular
			vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
			vec3 LightReflect = normalize(reflect(-light.positionOrDirection.xyz, Normal0));
			float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
			SpecularFactor = pow( SpecularFactor, object.specularExp);
			vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;
			
			directionalTerm += specularTerm;
		}
		totalLight += directionalTerm;

		if (light.positionOrDirection.w == 1.0f && light.isSpot != 1) {
			vec3 directionToPosLight = normalize(light.positionOrDirection.xyz - WorldPos0 );

			// Diffuse
			float DiffuseFactor = max(dot(Normal0, directionToPosLight), 0.0f);
			vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * light.diffuseColor;

			// Specular
			vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
			vec3 LightReflect = normalize(reflect(-directionToPosLight, Normal0) );
			float SpecularFactor = max( dot( VertexToEye, LightReflect ), 0.0f);

			SpecularFactor = pow(SpecularFactor, object.specularExp);
		
			vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;
		
			positionalTerm = diffuseTerm + specularTerm;
		}
		totalLight += positionalTerm;

		if (light.isSpot == 1) {
			vec3 LightToPixel = normalize(WorldPos0 - light.positionOrDirection.xyz);
		
			float spotCosFactor = dot(LightToPixel, light.spotDirection);

			if( spotCosFactor > light.spotCutoffCos ) {
				vec3 directionToSpotLight = - LightToPixel;

				// Diffuse
				float DiffuseFactor = max(dot(Normal0, directionToSpotLight), 0.0f);
				vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * light.diffuseColor;

				// Specular
				vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
				vec3 LightReflect = normalize(reflect(-directionToSpotLight, Normal0));
				float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);

				SpecularFactor = pow(SpecularFactor, object.specularExp);

				vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;

				spotTerm = diffuseTerm + specularTerm;

				// Traditional method for attenuating illumination
				// near the edges of the cone
				// float falloff = pow( spotCosFactor, 50.0f );
			
				// Alternative method for attenuating illumination
				// near the edges of the cone
				float falloff = 1.0f - (1.0f - spotCosFactor) / (1.0f - light.spotCutoffCos);
			
				spotTerm = falloff * spotTerm;
			}
		}
		totalLight += spotTerm;
	}

	return totalLight;
}

const vec4 fogColor = vec4(0.75f, 0.75f, 0.75f, 1.0f);
const float fogEnd = 20.0f;
const float fogStart = 1.0f;

const float fogDensity = 0.32f;

float distanceFromViewPoint;

float linearFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);

	return max((fogEnd - distanceFromViewPoint)/(fogEnd - fogStart), 0.0f);
}

float exponentialFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);

	return exp( -(fogDensity * distanceFromViewPoint));
}

float exponentialTwoFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);

	return exp( - pow((fogDensity * distanceFromViewPoint),2));
}

void main()
{
	Material texturedMaterial = object;

	float fogFactor = linearFogFactor();

	if (object.textureMapped == true) {

		texturedMaterial.ambientMat = texture2D(gSampler, TexCoord0.st);
		texturedMaterial.diffuseMat = texture2D(gSampler, TexCoord0.st);
		texturedMaterial.specularMat = texture2D(gSampler, TexCoord0.st);
	}

	FragColor = object.emissiveMat;

	for (int i = 0; i < MaxLights; i++)  {
	
		FragColor += calcLight( lights[i], texturedMaterial );
	}

	//FragColor = fogFactor * FragColor + (1-fogFactor) * fogColor;

	FragColor.a = object.diffuseMat.a;
}