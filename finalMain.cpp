//
//  finalMain.cpp
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Jietong Chen
//
//  Main program for lighting/shading/texturing assignment
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

#endif

#ifndef __APPLE__

#include <GL/glew.h>

#endif

#include <GLFW/glfw3.h>

#include "Buffers.h"
#include "ShaderSetup.h"
#include "Canvas.h"
#include "Shapes.h"
#include "Lighting.h"
#include "Textures.h"
#include "Camera.h"
#include "Object.h"

using namespace std;

// do we need to do a display() call?
bool updateDisplay = true;

// our drawing canvas
Canvas *canvas;

// dimensions of the drawing window
int w_width = 1024;
int w_height = 870;

// camera of the scene
Camera camera[3];
// current actived camera
int currentCamera;

// all objects in the scene
vector< Object > object;

// Animation flag
bool animating = false;

// Initial animation rotation angles for the objects
GLfloat angles = 0.0f;

// program IDs...for shader programs
GLuint pshader, gshader, tshader;

///
// Create vertex and element buffers for a shape.
//
// @param obj - which shape to create
// @param C   - the Canvas to use
///
void createShape( int obj, Canvas &C ) {
    // clear any previous shape
    C.clear();

    // make the shape
    makeShape( obj, C );
}

///
// Create the cameras in the scene.
///
void createCamera() {
    // the aspect ratio of the camera
    float aspect = float( w_width ) / float( w_height );

    camera[ 0 ] = Camera( vec3( 0.0f, 3.65f, 11.3f ),
                          vec3( 0.0f, 1.5f, 0.0f ),
                          30.0f, aspect, 1.0f, 100.0f );

    camera[ 1 ] = Camera( vec3( -3.2f, 2.8f, 5.0f ),
                          vec3( 2.0f, 1.2f, -1.4f ),
                          30.0f, aspect, 1.0f, 100.0f );

    camera[ 2 ] = Camera( vec3( -0.3f, 15.0f, 4.0f ),
                          vec3( 0.0f, 0.8f, 0.0f ),
                          30.0f, aspect, 1.0f, 100.0f );

    // set the current actived camera
    currentCamera = 0;
}

///
// Initialize the shader programs.
///
void initShader() {
    // Load shaders, verifying each
    ShaderError error;
    pshader = shaderSetup( "phong.vert", "phong.frag", &error );
    if( !pshader ) {
        cerr << "Error setting up Phong shader - " <<
             errorString( error ) << endl;
        glfwTerminate();
        exit( 1 );
    }

    gshader = shaderSetup( "glass.vert", "glass.frag", &error );
    if( !gshader ) {
        cerr << "Error setting up Phong shader - " <<
             errorString( error ) << endl;
        glfwTerminate();
        exit( 1 );
    }

    tshader = shaderSetup( "texture.vert", "texture.frag", &error );
    if( !tshader ) {
        cerr << "Error setting up texture shader - " <<
             errorString( error ) << endl;
        glfwTerminate();
        exit( 1 );
    }
}

///
// Create every objects in the scene and set up the material properties and
// the model transformation.
///
void createObject() {
    // the table
    createShape( OBJ_TABLE, *canvas );
    Object table = Object( pshader, *canvas );

    table.material.ambientColor = vec4( 0.1f, 0.5f, 0.9f, 1.0f );
    table.material.diffuseColor = vec4( 0.18f, 0.19f, 0.19f, 1.0f );
    table.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    table.material.ka = 0.1f;
    table.material.kd = 0.9f;
    table.material.ks = 1.0f;
    table.material.shininess = 48.0f;

    table.translate( 0.0f, -0.1f, 0.0f );

    object.push_back( table );

    // the yellow teapot
    createShape( OBJ_TEAPOT, *canvas );
    Object teapot = Object( pshader, *canvas );

    teapot.material.ambientColor = vec4( 0.949f, 0.804f, 0.149f, 1.0f );
    teapot.material.diffuseColor = vec4( 0.949f, 0.804f, 0.149f, 1.0f );
    teapot.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    teapot.material.ka = 0.7f;
    teapot.material.kd = 0.9f;
    teapot.material.ks = 1.0f;
    teapot.material.shininess = 48.0f;

    teapot.scale( 2.43f, 2.43f, 2.43f );
    teapot.rotateY( 145.0f );
    teapot.translate( 1.19f, 0.0f, -1.48f );

    object.push_back( teapot );

    // the cup with blueberry texture
    createShape( OBJ_CUP, *canvas );
    Object cup = Object( tshader, *canvas );

    cup.material.ka = 0.7f;
    cup.material.kd = 1.0f;
    cup.material.ks = 1.0f;
    cup.material.shininess = 48.0f;

    cup.texture = Texture::cup;

    cup.rotateY( -28.0f );
    cup.translate( 2.05f, 0.0f, 0.34f );

    object.push_back( cup );

    // the sliver spoon
    createShape( OBJ_SPOON, *canvas );
    Object spoon = Object( pshader, *canvas );

    spoon.material.ambientColor = vec4( 0.672f, 0.637f, 0.585f, 1.0f );
    spoon.material.diffuseColor = vec4( 0.672f, 0.637f, 0.585f, 1.0f );
    spoon.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    spoon.material.ka = 0.2f;
    spoon.material.kd = 0.7f;
    spoon.material.ks = 1.0f;
    spoon.material.shininess = 10.0f;

    spoon.scale( 1.35f, 1.35f, 1.35f );
    spoon.rotateY( 9.0f );
    spoon.translate( 1.58f, 0.0f, 1.5f );

    object.push_back( spoon );

    // the porcelain plate
    createShape( OBJ_PLATE, *canvas );
    Object plate = Object( pshader, *canvas );

    plate.material.ambientColor = vec4( 0.992f, 1.0f, 0.988f, 1.0f );
    plate.material.diffuseColor = vec4( 0.992f, 1.0f, 0.988f, 1.0f );
    plate.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    plate.material.ka = 0.5f;
    plate.material.kd = 0.7f;
    plate.material.ks = 1.0f;
    plate.material.shininess = 10.0f;

    plate.scale( 1.05f, 1.05f, 1.05f );
    plate.translate( -0.65f, 0.0f, 1.1f );

    object.push_back( plate );

    // the first doughnut
    createShape( OBJ_DOUGHNUT, *canvas );
    Object doughnut1 = Object( pshader, *canvas );

    doughnut1.material.ambientColor = vec4( 0.788f, 0.439f, 0.078f, 1.0f );
    doughnut1.material.diffuseColor = vec4( 0.788f, 0.439f, 0.078f, 1.0f );
    doughnut1.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    doughnut1.material.ka = 0.5f;
    doughnut1.material.kd = 0.7f;
    doughnut1.material.ks = 0.3f;
    doughnut1.material.shininess = 10.0f;

    doughnut1.scale( 0.67f, 0.67f, 0.67f );
    doughnut1.rotateX( -84.0f );
    doughnut1.rotateY( 40.0f );
    doughnut1.translate( -1.7f, 1.6f, -1.3f );

    object.push_back( doughnut1 );

    // the second doughnut
    Object doughnut2 = Object( pshader, *canvas );
    doughnut2.material = doughnut1.material;

    doughnut2.scale( 0.6f, 0.6f, 0.6f );
    doughnut2.rotateX( -68.0f );
    doughnut2.rotateY( -118.0f );
    doughnut2.translate( -2.2f, 1.6f, -1.7f );

    object.push_back( doughnut2 );

    // the first yellow apple
    createShape( OBJ_APPLE, *canvas );
    Object apple1 = Object( pshader, *canvas );

    apple1.material.ambientColor = vec4( 0.873f, 0.363f, 0.128f, 1.0f );
    apple1.material.diffuseColor = vec4( 0.973f, 0.851f, 0.008f, 1.0f );
    apple1.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    apple1.material.ka = 0.5f;
    apple1.material.kd = 0.9f;
    apple1.material.ks = 0.3f;
    apple1.material.shininess = 16.0f;

    apple1.scale( 0.82f, 0.82f, 0.82f );
    apple1.rotateX( 6.0f );
    apple1.rotateY( 298.0f );
    apple1.translate( -0.68f, 0.0f, -1.3f );

    object.push_back( apple1 );

    // the second yellow apple
    Object apple2 = Object( pshader, *canvas );
    apple2.material = apple1.material;

    apple2.scale( 0.87f, 0.87f, 0.87f );
    apple2.rotateY( -15.0f );
    apple2.rotateX( 40.0f );
    apple2.rotateZ( -74.0f );
    apple2.translate( -2.85f, 0.3f, -0.8f );

    object.push_back( apple2 );

    // the first pirouline cookies
    createShape( OBJ_COOKIES1, *canvas );
    Object cookies1 = Object( pshader, *canvas );

    cookies1.material.ambientColor = vec4( 0.847f, 0.490f, 0.071f, 1.0f );
    cookies1.material.diffuseColor = vec4( 0.961f, 0.843f, 0.6f, 1.0f );
    cookies1.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    cookies1.material.ka = 1.0f;
    cookies1.material.kd = 0.7f;
    cookies1.material.ks = 0.1f;
    cookies1.material.shininess = 1.0f;

    cookies1.scale( 0.54f, 0.54f, 0.54f );
    cookies1.rotateZ( 155.0f );
    cookies1.rotateX( 5.0f );
    cookies1.rotateY( -31.0f );
    cookies1.translate( -0.38f, 0.278f, 1.08f );

    object.push_back( cookies1 );

    // the second pirouline cookies
    Object cookies2 = Object( pshader, *canvas );
    cookies2.material = cookies1.material;

    cookies2.scale( 0.54f, 0.54f, 0.51f );
    cookies2.rotateZ( -84.0f );
    cookies2.rotateX( 3.0f );
    cookies2.rotateY( -32.0f );
    cookies2.translate( -0.65f, 0.278f, 1.03f );

    object.push_back( cookies2 );

    // the third pirouline cookies
    Object cookies3 = Object( pshader, *canvas );
    cookies3.material = cookies1.material;

    cookies3.scale( 0.54f, 0.54f, 0.52f );
    cookies3.rotateZ( -147.0f );
    cookies3.rotateX( -9.0f );
    cookies3.rotateY( -41.0f );
    cookies3.translate( -1.12f, 0.338f, 1.18f );

    object.push_back( cookies3 );

    // the fourth short pirouline cookies
    createShape( OBJ_COOKIES2, *canvas );
    Object cookies4 = Object( pshader, *canvas );
    cookies4.material = cookies1.material;

    cookies4.scale( 0.50f, 0.50f, 0.50f );
    cookies4.rotateZ( -83.0f );
    cookies4.rotateY( 11.0f );
    cookies4.translate( -2.05f, 0.124f, 1.37f );

    object.push_back( cookies4 );

    // the fifth short pirouline cookies
    Object cookies5 = Object( pshader, *canvas );
    cookies5.material = cookies1.material;

    cookies5.scale( 0.6f, 0.6f, 0.432f );
    cookies5.rotateZ( -102.0f );
    cookies5.rotateY( 240.0f );
    cookies5.translate( -2.64f, 0.1536f, 1.21f );

    object.push_back( cookies5 );

    // the big foliage
    createShape( OBJ_QUAD, *canvas );
    Object foliage1 = Object( tshader, *canvas );

    foliage1.material.ka = 0.5f;
    foliage1.material.kd = 1.0f;
    foliage1.material.ks = 0.7f;
    foliage1.material.shininess = 10.0f;

    foliage1.texture = Texture::foliage1;

    foliage1.scale( 1.16f, 1.16f, 1.16f );
    foliage1.rotateX( -9.0f );
    foliage1.rotateZ( 22.0f );
    foliage1.translate( -2.5f, 2.7f, -2.5f );

    object.push_back( foliage1 );

    // the first small foliage
    createShape( OBJ_FOLIAGE, *canvas );
    Object foliage2 = Object( tshader, *canvas );

    foliage2.material = foliage1.material;
    foliage2.texture = Texture::foliage2;

    foliage2.scale( 0.38f, 0.32f, 0.38f );
    foliage2.rotateX( -53.0f );
    foliage2.rotateY( -128.0f );
    foliage2.translate( 0.9f, 0.1f, 0.5f );

    object.push_back( foliage2 );

    // the second small foliage
    Object foliage3 = Object( tshader, *canvas );

    foliage3.material = foliage1.material;
    foliage3.texture = Texture::foliage3;

    foliage3.scale( 0.47f, 0.47f, 0.47f );
    foliage3.rotateZ( 28.0f );
    foliage3.rotateX( 66.0f );
    foliage3.rotateY( 3.0f );
    foliage3.translate( -1.1f, 2.05f, -2.0f );

    object.push_back( foliage3 );

    // the third small foliage
    Object foliage4 = Object( tshader, *canvas );

    foliage4.material = foliage1.material;
    foliage4.texture = Texture::foliage4;

    foliage4.scale( 0.77f, 0.77f, 0.77f );
    foliage4.rotateZ( 8.0f );
    foliage4.rotateX( 55.0f );
    foliage4.rotateY( -41.0f );
    foliage4.translate( -0.8f, 2.1f, -2.0f );

    object.push_back( foliage4 );

    // the fourth small foliage
    Object foliage5 = Object( tshader, *canvas );

    foliage5.material = foliage1.material;
    foliage5.texture = Texture::foliage3;

    foliage5.scale( 0.7f, 0.7f, 0.7f );
    foliage5.rotateX( 124.0f );
    foliage5.rotateY( -48.0f );
    foliage5.translate( -2.4f, 1.65f, -0.7f );

    object.push_back( foliage5 );

    // the fifth small foliage
    Object foliage6 = Object( tshader, *canvas );

    foliage6.material = foliage1.material;
    foliage6.texture = Texture::foliage4;

    foliage6.scale( 0.89f, 0.89f, 0.89f );
    foliage6.rotateZ( -4.0f );
    foliage6.rotateX( 149.0f );
    foliage6.rotateY( -68.0f );
    foliage6.translate( -2.7f, 1.8f, -1.0f );

    object.push_back( foliage6 );

    // the glass pot
    createShape( OBJ_POT, *canvas );
    Object pot = Object( gshader, *canvas );

    pot.material.ambientColor = vec4( 0.769f, 0.992f, 0.969f, 0.5f );
    pot.material.diffuseColor = vec4( 0.769f, 0.992f, 0.969f, 0.5f );
    pot.material.specularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    pot.material.ka = 1.0f;
    pot.material.kd = 0.2f;
    pot.material.ks = 1.0f;
    pot.material.shininess = 48.0f;

    pot.scale( 1.76f, 1.76f, 1.76f );
    pot.translate( -1.8f, 0.0f, -1.4f );

    object.push_back( pot );
}

///
// OpenGL initialization
///
void init( void ) {
    // Create our Canvas
    canvas = new Canvas( w_width, w_height );

    if( canvas == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
        glfwTerminate();
        exit( 1 );
    }

    // Load texture image(s)
    loadTexture();

    // create the cameras
    createCamera();

    // initialize the shader programs
    initShader();

    // Other OpenGL initialization
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0f );

    // Create all our objects
    createObject();
}

///
// Display callback
//
// Invoked whenever the image must be redrawn
///
void display( void ) {
    // clear and draw params..
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // draw all objects
    for( int i = 0; i < object.size(); i++ ) {
        object[ i ].drawObject();
    }
}

///
// Keyboard callback
//
// We don't need to distinguish between (e.g.) 'a' and 'A', so
// we can use the simpler form of callback
///
void keyboard( GLFWwindow *window, int key, int scan, int action, int mods ) {
    if( action != GLFW_PRESS )    // only activate on press, not rpt/release
        return;

    switch( key ) {

        case GLFW_KEY_1:
            // switch to the first camera
            currentCamera = 0;
            break;

        case GLFW_KEY_2:
            // switch to the second camera
            currentCamera = 1;
            break;

        case GLFW_KEY_3:
            // switch to the third camera
            currentCamera = 2;
            break;

        case GLFW_KEY_A:    // animate
            animating = true;
            break;

        case GLFW_KEY_S:    // stop animating
            animating = false;
            break;

        case GLFW_KEY_R:    // reset transformations
            camera[ 0 ].position = vec3( 0.0f, 3.65f, 11.3f );
            angles = 0.0f;
            break;

        case GLFW_KEY_ESCAPE:   // terminate the program
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose( window, 1 );
            break;
    }

    updateDisplay = true;
}

///
// Animate the first camera.
///
void animate( void ) {
    if( animating ) {
        // rotate the first camera
        angles += 0.75f;

        if( angles >= 360.0f ) {
            angles = 0.0f;
        }

        camera[ 0 ].position = vec3(
                11.3f * sinf( angles * float( M_PI ) / 180.0f ), 3.65f,
                11.3f * cosf( angles * float( M_PI ) / 180.0f ) );

        updateDisplay = true;
    }
}

void glfwError( int code, const char *desc ) {
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}

///
// main program for the final project
///
int main( int argc, char **argv ) {

    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    // NOTE:  Mac users may need to uncomment the following four lines
    // in order to force an OpenGL 3.2 (or better) context

    // glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    // glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
    // glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    // glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
                                           "The Color of Tea", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: " << glewGetErrorString( err ) << endl;
        glfwTerminate();
        exit( 1 );
    }
    if( !GLEW_VERSION_3_2 ) {
        cerr << "GLEW: OpenGL 3.2 not available" << endl;
        if( !GLEW_VERSION_2_1 ) {
            cerr << "GLEW: OpenGL 2.1 not available, either!" << endl;
            glfwTerminate();
            exit( 1 );
        }
    }
#endif

    // determine whether or not we can use GLSL 1.50
    int maj = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MAJOR );
    int min = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MINOR );

    cerr << "GLFW: using " << maj << "." << min << " context" << endl;
    if( maj < 3 || ( maj == 3 && min < 2 ) ) {
        // nope!
        cerr << "*** GLSL 1.50 shaders may not compile" << endl;
    }

    init();

    glfwSetKeyCallback( window, keyboard );

    while( !glfwWindowShouldClose( window ) ) {
        animate();
        if( updateDisplay ) {
            updateDisplay = false;
            display();
            glfwSwapBuffers( window );
        }
        glfwPollEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();


    return 0;
}
