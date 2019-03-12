//
//  Textures
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Jietong Chen
//
//  Simple class for setting up texture mapping parameters.
//
//  This code can be compiled as either C or C++.
//

#ifdef __cplusplus

#include <iostream>

#else
#include <stdio.h>
#endif

#include "Textures.h"

// this is here in case you are using SOIL;
// if you're not, it can be deleted.
#include <SOIL.h>
#include <cstdio>

#ifdef __cplusplus
using namespace std;
#endif

// the texture handle of cup
GLuint Texture::cup;
// the texture handle of foliage
GLuint Texture::foliage1;
GLuint Texture::foliage2;
GLuint Texture::foliage3;
GLuint Texture::foliage4;

///
// This function loads texture data for the GPU.
///
void loadTexture() {
    // load the cup image by SOIL
    Texture::cup = SOIL_load_OGL_texture( "texture/blueberry.png",
                                          SOIL_LOAD_AUTO,
                                          SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_MIPMAPS |
                                          SOIL_FLAG_INVERT_Y |
                                          SOIL_FLAG_NTSC_SAFE_RGB |
                                          SOIL_FLAG_COMPRESS_TO_DXT );

    if( Texture::cup == 0 ) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // set up the texture parameters
    glBindTexture( GL_TEXTURE_2D, Texture::cup );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    // load the first foliage image by SOIL
    Texture::foliage1 = SOIL_load_OGL_texture( "texture/foliage1.png",
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS |
                                               SOIL_FLAG_INVERT_Y |
                                               SOIL_FLAG_NTSC_SAFE_RGB |
                                               SOIL_FLAG_COMPRESS_TO_DXT );

    if( Texture::foliage1 == 0 ) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // set up the texture parameters
    glBindTexture( GL_TEXTURE_2D, Texture::foliage1 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    // load the second foliage image by SOIL
    Texture::foliage2 = SOIL_load_OGL_texture( "texture/foliage2.png",
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS |
                                               SOIL_FLAG_INVERT_Y |
                                               SOIL_FLAG_NTSC_SAFE_RGB |
                                               SOIL_FLAG_COMPRESS_TO_DXT );

    if( Texture::foliage2 == 0 ) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // set up the texture parameters
    glBindTexture( GL_TEXTURE_2D, Texture::foliage2 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    // load the third foliage image by SOIL
    Texture::foliage3 = SOIL_load_OGL_texture( "texture/foliage3.png",
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS |
                                               SOIL_FLAG_INVERT_Y |
                                               SOIL_FLAG_NTSC_SAFE_RGB |
                                               SOIL_FLAG_COMPRESS_TO_DXT );

    if( Texture::foliage3 == 0 ) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // set up the texture parameters
    glBindTexture( GL_TEXTURE_2D, Texture::foliage3 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    // load the fourth foliage image by SOIL
    Texture::foliage4 = SOIL_load_OGL_texture( "texture/foliage4.png",
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS |
                                               SOIL_FLAG_INVERT_Y |
                                               SOIL_FLAG_NTSC_SAFE_RGB |
                                               SOIL_FLAG_COMPRESS_TO_DXT );

    if( Texture::foliage4 == 0 ) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    // set up the texture parameters
    glBindTexture( GL_TEXTURE_2D, Texture::foliage4 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

///
// This function sets up the parameters for texture use.
//
// @param texture - The OpenGL texture handle of the texture to use
///
void setUpTexture( GLuint texture ) {
    glBindTexture( GL_TEXTURE_2D, texture );
}
