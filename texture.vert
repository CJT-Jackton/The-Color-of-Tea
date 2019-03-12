#version 130

// Texture mapping vertex shader
//
// Contributor:  Jietong Chen

// INCOMING DATA

// Vertex location (in model space)
in vec4 vPosition;

// Normal vector at vertex (in model space)
in vec3 vNormal;

// Texture coordinate for this vertex
in vec2 vTexCoord;

// Model transformations
uniform mat4 modelMat;

// Viewing matrix
uniform mat4 viewMat;

// Projection matrix
uniform mat4 projectionMat;

// Normal matrix
uniform mat3 normalMat;

// Point light position (in world space)
uniform vec4 pLightPosition;

// OUTGOING DATA

// Vertex location (in camera space)
out vec3 position;

// Normal vector at vertex (in camera space)
out vec3 normal;

// Texture coordinate for this vertex
out vec2 texCoord;

// Point light position (in camera space)
out vec3 pLightPos;

//
// Main function
//

void main()
{
    // convert the vertex location into camera space
    position = ( viewMat * modelMat * vPosition ).xyz;

    // convert the normal vector into camera space
    normal = normalMat * vNormal;

    // simply pass the texture coordinate
    texCoord = vTexCoord;

    // convert the point light position into camera space
    pLightPos = ( viewMat * pLightPosition ).xyz;

    // Transform the vertex location into clip space
    gl_Position =  projectionMat * viewMat  * modelMat * vPosition;
}
