#version 130

// Texture mapping vertex shader
//
// Contributor:  Jietong Chen

// INCOMING DATA

// Vertex location (in camera space)
in vec3 position;

// Normal vector at vertex (in camera space)
in vec3 normal;

// Texture coordinate for this vertex
in vec2 texCoord;

// Point light position (in camera space)
in vec3 pLightPos;

// struct of material properties
struct Material
{
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

// Texture of front face
uniform sampler2D tex;

// OUTGOING DATA
out vec4 finalColor;

void main()
{
    // the front facing texture color
    vec4 texColor = texture( tex, texCoord );

    if( texColor.a < 0.1 ) {
        // omit the fragment with alpha channel < 0.1
        discard;
    }

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
    vec3 aColor = aLightColor.rgb * material.ka * texColor.rgb;

    // the diffuse color
    vec3 dColor = pLightColor.rgb * material.kd * texColor.rgb *
                  max( dot( n, l ), 0 );

    // the specular highlight
    float spec = pow( max( dot( v, r ), 0 ), material.shininess );
    // the specular highlight(Blinn-Phong shading)
    // float spec = pow( max( dot( n, h ), 0 ), material.shininess );

    // the specular color
    vec3 sColor = pLightColor.rgb * material.ks * texColor.rgb * spec;

    finalColor = vec4( aColor + dColor + sColor, texColor.a );
}
