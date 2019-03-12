//
// Material.h
//
// Material class of material surface properties.
//
// Author:  Jietong Chen
// Date:    5/2/2018
//

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>

using namespace glm;

///
// Material class.
///
typedef struct Material {
    // the ambient material color
    vec4 ambientColor;
    // the diffuse material color
    vec4 diffuseColor;
    // the specular material color
    vec4 specularColor;

    // the ambient reflection coefficient
    float ka;
    // the diffuse reflection coefficient
    float kd;
    // the specular reflection coefficient
    float ks;

    // the specular exponent
    float shininess;
} Material;


#endif //_MATERIAL_H_
