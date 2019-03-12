#version 130

// Glass fragment shader
//
// Author:  Jietong Chen

// INCOMING

// Vertex location (in camera space)
in vec3 position;

// Normal vector at vertex (in camera space)
in vec3 normal;

// Point light position (in camera space)
in vec3 pLightPos;

// struct of material properties
struct Material
{
    // the ambient material color
    vec4 ambient;
    // the diffuse material color
    vec4 diffuse;
    // the specular material color
    vec4 specular;

    // the ambient reflection coefficient
    float ka;
    // the diffuse reflection coefficient
    float kd;
    // the specular reflection coefficient
    float ks;

    // the specular exponent
    float shininess;
};

// Material properties of the object
uniform Material material;

// Ambient light color
uniform vec4 aLightColor;

// Point light color
uniform vec4 pLightColor;

// OUTGOING DATA
out vec4 finalColor;

void main()
{
    // the normal vector
    vec3 n = normalize( normal );
    // the light direction vector
    vec3 l = normalize( pLightPos - position );
    // the viewing direction vector
    vec3 v = normalize( -position );
    // the reflection vector
    vec3 r = reflect( -l, n );
    // the half-way vector (Blinn-Phong shading)
    // vec3 h = normalize( l + v );

    // the ambient color
    vec3 aColor = aLightColor.rgb * material.ka * material.ambient.rgb;

    // the diffuse color
    vec3 dColor = pLightColor.rgb * material.kd * material.diffuse.rgb *
                  max( dot( n, l ), 0 );

    // the specular highlight
    float spec = pow( max( dot( v, r ), 0 ), material.shininess );
    // the specular highlight(Blinn-Phong shading)
    // float spec = pow( max( dot( n, h ), 0 ), material.shininess );

    // the specular color
    vec4 sColor = pLightColor * material.ks * material.specular * spec;

    // Fresnel-Schlick's approximation
    // idea and code from Joey De Vries https://learnopengl.com/PBR/Theory
    // 0.08 is the normal incidence of glass
    vec3 F0 = vec3( 0.08 );

    // 0.5 is the metallic of the material, the value is from the table of
    // docs.unrealengine.com/en-us/Engine/Rendering/Materials/PhysicallyBased
    F0 = mix( F0, aColor + dColor, 0.5 );

    // Fresnel effect with an exponent 5 (the fall off)
    vec3 fresnel = F0 + ( 1.0 - F0 ) * pow( 1.0 - max( dot( n, v ), 0 ), 5.0 );

    // adding transparency to the object with the fresnel value
    finalColor = vec4( fresnel, fresnel.x ) + sColor;
}
