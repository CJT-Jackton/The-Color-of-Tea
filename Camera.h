//
// Camera.h
//
// Camera class.
//
// Author:  Jietong Chen
// Date:    5/2/2018
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

///
// A camera in 3D scene.
///
class Camera {

public:
    // camera location in world space
    vec3 position;

    // lookat point location in world space
    vec3 lookat;

    // up vector
    vec3 up;

    // clipping window boundaries
    float znear;
    float zfar;

    // field of view in degree
    float fov;

    // aspect ratio of clipping window
    float aspect;

    ///
    // Constructor
    //
    // @param position - camera location
    // @param lookat   - lookat point location
    // @param fov      - field of view
    // @param aspect   - aspect ratio
    // @param near     - near clipping plate
    // @param far      - far clipping plate
    ///
    Camera( vec3 position = vec3( 0.0f ),
            vec3 lookat = vec3( 0.0f, 0.0f, -1.0f ),
            float fov = 45.0f, float aspect = 1.0f, float near = 1.0f,
            float far = 100.0f );

    ///
    // Get the viewing transformation matrix of the camera.
    //
    // @return the viewing transformation matrix
    ///
    mat4 getViewMat();

    ///
    // Get the projection matrix of the camera.
    //
    // @return the projection matrix
    ///
    mat4 getProjectionMat();
};

#endif //_CAMERA_H_
