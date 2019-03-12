//
//  Textures.h
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Jietong Chen
//
//  Simple class for setting up texture mapping parameters.
//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

#endif

#ifndef __APPLE__

#include <GL/glew.h>

#endif

#include <GLFW/glfw3.h>

///
// A simple texture class with texture handles.
///
class Texture {

public:
    // the texture handle of cup
    static GLuint cup;
    // the texture handle of foliages
    static GLuint foliage1;
    static GLuint foliage2;
    static GLuint foliage3;
    static GLuint foliage4;
};

///
// This function loads texture data for the GPU.
///
void loadTexture();

///
// This function sets up the parameters for texture use.
//
// @param texture - The OpenGL texture handle of the texture to use
///
void setUpTexture( GLuint texture );

#endif 
