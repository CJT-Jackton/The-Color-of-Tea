//
//  Lighting
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Jietong Chen
//
//  Simple class for setting up Phong illumination/shading.
//
//  This code can be compiled as either C or C++.
//

#include "Lighting.h"

///
// Set up the lighting properties of the scene.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpLight( GLuint program ) {
    // set up the ambient light property
    GLfloat ambientLightColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glUniform4fv( glGetUniformLocation( program, "aLightColor" ), 1,
                  ambientLightColor );

    // set up the point light properties
    GLfloat pointLightPosition[4] = { -30.0f, 60.0f, 20.0f, 1.0f };
    GLfloat pointLightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glUniform4fv( glGetUniformLocation( program, "pLightPosition" ), 1,
                  pointLightPosition );
    glUniform4fv( glGetUniformLocation( program, "pLightColor" ), 1,
                  pointLightColor );
}
