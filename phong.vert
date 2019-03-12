#version 130

// Phong vertex shader
//
// Contributor:  Jietong Chen

// INCOMING DATA

// Vertex location (in model space)
in vec4 vPosition;

// Normal vector at vertex (in model space)
in vec3 vNormal;

// Model transformations matrix
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

    // convert the point light position into camera space
    pLightPos = ( viewMat * pLightPosition ).xyz;

    // Transform the vertex location into clip space
    gl_Position =  projectionMat * viewMat  * modelMat * vPosition;
}
