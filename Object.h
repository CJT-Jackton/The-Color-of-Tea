//
// Object.h
//
// A class of object in the scene.
//
// Author:  Jietong Chen
// Date:    5/2/2018
//

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Buffers.h"
#include "Material.h"

// Macros for object and shading selection
#define OBJ_APPLE    0
#define OBJ_COOKIES1 1
#define OBJ_COOKIES2 2
#define OBJ_CUP      3
#define OBJ_DOUGHNUT 4
#define OBJ_FOLIAGE  5
#define OBJ_PLATE    6
#define OBJ_POT      7
#define OBJ_QUAD     8
#define OBJ_SPOON    9
#define OBJ_TABLE    10
#define OBJ_TEAPOT   11

///
// A simple object class with all properties needed to rendering an object.
///
class Object {

private:

    ///
    // Set up the buffer.
    ///
    void setUpBuffer();

    ///
    // Set up the model, view, projection matrix.
    ///
    void setUpMatrix();

    ///
    // Set up the material properties.
    ///
    void setUpMaterial();

public:

    // buffer of
    BufferSet bufferSet;

    // material properties
    Material material;

    // the ID of an OpenGL (GLSL) shader program
    GLuint program;

    // the OpenGL texture handle
    GLuint texture;

    // Model transformation matrix
    mat4 Model;

    ///
    // Default constructor
    ///
    Object();

    ///
    // Constructor
    //
    // @param program - the ID of an OpenGL (GLSL) shader program to which
    //     parameter values are to be sent
    // @param C       - the Canvas to use
    ///
    Object( GLuint program, Canvas &C );

    ///
    // Draw the object.
    ///
    void drawObject();

    ///
    // Reset the model transformation of the object.
    ///
    void reset();

    ///
    // This function perfrom a scaling operation.
    //
    // @param scaleX - amount of scaling along the x-axis
    // @param scaleY - amount of scaling along the y-axis
    // @param scaleZ - amount of scaling along the z-axis
    ///
    void scale( GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ );

    ///
    // This function perfrom a translation operation.
    //
    // @param translateX - amount of translation along the x axis
    // @param translateY - amount of translation along the y axis
    // @param translateZ - amount of translation along the z axis
    ///
    void translate( GLfloat translateX, GLfloat translateY,
                    GLfloat translateZ );

    ///
    // This function perform of rotation around the x axis.
    //
    // @param rotateX - angle of rotation around the x-axis, in degrees
    ///
    void rotateX( GLfloat rX );

    ///
    // This function perform a rotation around the y axis.
    //
    // @param rotateY - angle of rotation around the y-axis, in degrees
    ///
    void rotateY( GLfloat rY );

    ///
    // This function perform a rotation around the z axis.
    //
    // @param rotateZ - angle of rotation around the z-axis, in degrees
    ///
    void rotateZ( GLfloat rZ );
};


#endif //_OBJECT_H_
