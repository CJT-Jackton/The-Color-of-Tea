//
// Created by hasee on 5/2/2018.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Object.h"
#include "Camera.h"
#include "Lighting.h"
#include "Textures.h"

// How to calculate an offset into the vertex buffer
#define BUFFER_OFFSET( i ) ((char *)NULL + (i))

///
// Default constructor
///
Object::Object() {
}

///
// Constructor
//
// @param program - the ID of an OpenGL (GLSL) shader program to which
//     parameter values are to be sent
// @param C       - the Canvas to use
///
Object::Object( GLuint program, Canvas &C ) {
    this->bufferSet.createBuffers( C );
    this->program = program;
    this->texture = 0;
    this->Model = mat4( 1.0f );
}

///
// Draw the object.
///
void Object::drawObject() {
    glUseProgram( program );

    // set up the buffer
    setUpBuffer();
    // set up the matrices
    setUpMatrix();
    // set up the surface material
    setUpMaterial();
    // set up the lighting properties
    setUpLight( program );

    // the object has texture
    if( texture != 0 ) {
        // set up the texture
        setUpTexture( texture );
    }

    // draw it
    glDrawElements( GL_TRIANGLES, bufferSet.numElements,
                    GL_UNSIGNED_INT, ( void * ) 0 );
}

///
// Set up the buffer.
///
void Object::setUpBuffer() {
    // bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, bufferSet.vbuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, bufferSet.ebuffer );

    // set up the vertex attribute variables
    GLint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET( 0 ) );
    int offset = bufferSet.vSize;

    if( bufferSet.cSize ) {  // color data
        GLint vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET( offset ) );
        offset += bufferSet.cSize;
    }

    if( bufferSet.nSize ) {  // normal data
        GLint vNormal = glGetAttribLocation( program, "vNormal" );
        glEnableVertexAttribArray( vNormal );
        glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET( offset ) );
        offset += bufferSet.nSize;
    }

    if( bufferSet.tSize ) {  // texture coordinate data
        GLint vTexCoord = glGetAttribLocation( program, "vTexCoord" );
        glEnableVertexAttribArray( vTexCoord );
        glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET( offset ) );
        offset += bufferSet.tSize;
    }
}

///
// Set up the model, view, projection matrix.
///
void Object::setUpMatrix() {
    extern Camera camera[3];
    extern int currentCamera;

    // the viewing matrix of current camera
    mat4 View = camera[ currentCamera ].getViewMat();

    // the projection matrix of current camera
    mat4 Projection = camera[ currentCamera ].getProjectionMat();

    // the normal matrix
    mat3 Normal = mat3( inverseTranspose( View * Model ) );

    // set up the model matrix
    glUniformMatrix4fv( glGetUniformLocation( program, "modelMat" ),
                        1, GL_FALSE, value_ptr( Model ) );

    // set up the viewing matrix
    glUniformMatrix4fv( glGetUniformLocation( program, "viewMat" ),
                        1, GL_FALSE, value_ptr( View ) );

    // set up the projection matrix
    glUniformMatrix4fv( glGetUniformLocation( program, "projectionMat" ),
                        1, GL_FALSE, value_ptr( Projection ) );

    // set up the normal matrix
    glUniformMatrix3fv( glGetUniformLocation( program, "normalMat" ),
                        1, GL_FALSE, value_ptr( Normal ) );
}

///
// Set up the material properties.
///
void Object::setUpMaterial() {
    glUniform4fv( glGetUniformLocation( program, "material.ambient" ), 1,
                  value_ptr( material.ambientColor ) );
    glUniform4fv( glGetUniformLocation( program, "material.diffuse" ), 1,
                  value_ptr( material.diffuseColor ) );
    glUniform4fv( glGetUniformLocation( program, "material.specular" ), 1,
                  value_ptr( material.specularColor ) );

    glUniform1f( glGetUniformLocation( program, "material.ka" ),
                 material.ka );
    glUniform1f( glGetUniformLocation( program, "material.kd" ),
                 material.kd );
    glUniform1f( glGetUniformLocation( program, "material.ks" ),
                 material.ks );

    glUniform1f( glGetUniformLocation( program, "material.shininess" ),
                 material.shininess );
}

///
// Reset the model transformation of the object.
///
void Object::reset() {
    Model = mat4( 1.0f );
}

///
// This function perfrom a scaling operation.
//
// @param scaleX - amount of scaling along the x-axis
// @param scaleY - amount of scaling along the y-axis
// @param scaleZ - amount of scaling along the z-axis
///
void Object::scale( GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ ) {
    mat4 Scale = mat4( 1.0f );

    Scale[ 0 ][ 0 ] = scaleX;
    Scale[ 1 ][ 1 ] = scaleY;
    Scale[ 2 ][ 2 ] = scaleZ;

    Model = Scale * Model;
}

///
// This function perfrom a translation operation.
//
// @param translateX - amount of translation along the x axis
// @param translateY - amount of translation along the y axis
// @param translateZ - amount of translation along the z axis
///
void Object::translate( GLfloat translateX, GLfloat translateY,
                        GLfloat translateZ ) {
    mat4 Translate = mat4( 1.0f );

    Translate[ 3 ][ 0 ] = translateX;
    Translate[ 3 ][ 1 ] = translateY;
    Translate[ 3 ][ 2 ] = translateZ;

    Model = Translate * Model;
}

///
// This function perform of rotation around the x axis.
//
// @param rotateX - angle of rotation around the x-axis, in degrees
///
void Object::rotateX( GLfloat rX ) {
    // radians of the degrees
    GLfloat rad = rX * 3.14159265f / 180.0f;
    GLfloat sin = glm::sin( rad );
    GLfloat cos = glm::cos( rad );

    mat4 RotateX = mat4( 1.0f );

    RotateX[ 1 ][ 1 ] = cos;
    RotateX[ 1 ][ 2 ] = sin;
    RotateX[ 2 ][ 1 ] = -sin;
    RotateX[ 2 ][ 2 ] = cos;

    Model = RotateX * Model;
}

///
// This function perform a rotation around the y axis.
//
// @param rotateY - angle of rotation around the y-axis, in degrees
///
void Object::rotateY( GLfloat rY ) {
    // radians of the degrees
    GLfloat rad = rY * 3.14159265f / 180.0f;
    GLfloat sin = glm::sin( rad );
    GLfloat cos = glm::cos( rad );

    mat4 RotateY = mat4( 1.0f );

    RotateY[ 0 ][ 0 ] = cos;
    RotateY[ 0 ][ 2 ] = -sin;
    RotateY[ 2 ][ 0 ] = sin;
    RotateY[ 2 ][ 2 ] = cos;

    Model = RotateY * Model;
}

///
// This function perform a rotation around the z axis.
//
// @param rotateZ - angle of rotation around the z-axis, in degrees
///
void Object::rotateZ( GLfloat rZ ) {
    // radians of the degrees
    GLfloat rad = rZ * 3.14159265f / 180.0f;
    GLfloat sin = glm::sin( rad );
    GLfloat cos = glm::cos( rad );

    mat4 RotateZ = mat4( 1.0f );

    RotateZ[ 0 ][ 0 ] = cos;
    RotateZ[ 0 ][ 1 ] = sin;
    RotateZ[ 1 ][ 0 ] = -sin;
    RotateZ[ 1 ][ 1 ] = cos;

    Model = RotateZ * Model;
}
