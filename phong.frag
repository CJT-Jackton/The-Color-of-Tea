#version 130

// Phong fragment shader
//
// Contributor:  Jietong Chen

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

    finalColor = vec4( aColor + dColor, material.diffuse.a ) + sColor;
}
