//
//  Canvas.h
//
//  Created by Warren R. Carithers 2016/09/30.
//  Based on a C++ version created by Joe Geigel.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Prototypes for routines for manipulating a simple canvas
//  holding point information along with color data.
//
//  This file should not be modified by students.
//

#ifndef _CANVAS_H_
#define _CANVAS_H_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

///
// Simple canvas class that allows for pixel-by-pixel rendering.
///

class Canvas {

    ///
    // canvas size information
    ///
    int width;
    int height;

public:

    ///
    // point-related data
    ///

    // vertex locations
    vector<float> points;
    float *pointArray;

    // associated normal vectors
    vector<float> normals;
    float *normalArray;

    // associated (u,v) coordinates
    vector<float> uv;
    float *uvArray;

    // associated color data
    vector<float> colors;
    float *colorArray;

    // element count and connectivity data
    int numElements;
    GLuint *elemArray;

    ///
    // current drawing color
    ///
    GLfloat currentColor[3]; // RGB only - A is fixed

    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    Canvas( int w, int h );

    ///
    // Destructor
    ///
    ~Canvas( void );

    ///
    // clears the canvas
    ///
    void clear( void );

    ///
    // adds a triangle to the current shape
    //
    // @param p0 first triangle vertex
    // @param p1 second triangle vertex
    // @param p2 final triangle vertex
    ///
    void addTriangle( glm::vec3 p0, glm::vec3 p1, glm::vec3 p2 );

    ///
    // adds a triangle to the current shape, along with (u,v) data
    //
    // @param p0 first triangle vertex
    // @param uv0 first vertex (u,v) data
    // @param p1 second triangle vertex
    // @param uv1 second vertex (u,v) data
    // @param p2 final triangle vertex
    // @param uv2 final vertex (u,v) data
    ///
    void addTriangleWithUV( glm::vec3 p0, glm::vec3 uv0,
                            glm::vec3 p1, glm::vec3 uv1,
                            glm::vec3 p2, glm::vec3 uv2 );

    ///
    // adds a triangle to the current shape, along with normal data
    //
    // @param p0 first triangle vertex
    // @param n0 first vertex normal data
    // @param p1 second triangle vertex
    // @param n1 second vertex normal data
    // @param p2 final triangle vertex
    // @param n2 final vertex normal data
    ///
    void addTriangleWithNorms( glm::vec3 p0, glm::vec3 n0,
                               glm::vec3 p1, glm::vec3 n1,
                               glm::vec3 p2, glm::vec3 n2 );

    ///
    // adds a triangle to the current shape, along with (u,v) and normal data
    //
    // @param p0 first triangle vertex
    // @param n0 first triangle normal data
    // @param uv0 first triangle (u,v) data
    // @param p1 second triangle vertex
    // @param n1 second triangle normal data
    // @param uv1 second triangle (u,v) data
    // @param p2 final triangle vertex
    // @param n2 final triangle normal data
    // @param uv2 final triangle (u,v) data
    ///
    void addTriangleWithNormsUV( glm::vec3 p0, glm::vec3 n0, glm::vec3 uv0,
                                 glm::vec3 p1, glm::vec3 n1, glm::vec3 uv1,
                                 glm::vec3 p2, glm::vec3 n2, glm::vec3 uv2 );

    ///
    // Sets the current color
    //
    // @param r The red component of the new color (between 0-1)
    // @param g The green component of the new color (between 0-1)
    // @param b The blue component of the new color (between 0-1);
    ///
    void setColor( float r, float g, float b );

    ///
    // writes a pixel using the current color
    //
    // @param x The x coord of the pixel to be set
    // @param y The y coord of the pixel to be set
    ///
    void setPixel( int x, int y );

    ///
    // retrieve the array of element data from this Canvas
    ///
    GLuint *getElements( void );

    ///
    // retrieve the array of vertex data from this Canvas
    ///
    float *getVertices( void );

    ///
    // retrieve the array of normal data from this Canvas
    ///
    float *getNormals( void );

    ///
    // retrieve the array of (u,v) data from this Canvas
    ///
    float *getUV( void );

    ///
    // retrieve the array of color data from this Canvas
    ///
    float *getColors( void );

    ///
    // retrieve the vertex count from this Canvas
    ///
    int numVertices( void );

};

#endif
