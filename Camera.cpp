//
// Camera.cpp
//
// Camera class implementations.
//
// Author:  Jietong Chen
// Date:    5/2/2018
//

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

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
Camera::Camera( vec3 position, vec3 lookat, float fov, float aspect, float near,
                float far ) : position( position ), lookat( lookat ),
                              fov( fov ), aspect( aspect ),
                              znear( near ), zfar( far ) {
    // default up vector
    up = vec3( 0.0f, 1.0f, 0.0f );
}

///
// Get the viewing transformation matrix of the camera.
//
// @return the viewing transformation matrix
///
mat4 Camera::getViewMat() {
    // n-axis of camera coordinate
    vec3 n = normalize( position - lookat );
    // u-axis of camera coordinate
    vec3 u = normalize( cross( up, n ) );
    // v-axis of camera coordinate
    vec3 v = normalize( cross( n, u ) );

    return mat4( u.x, v.x, n.x, 0.0f,
                 u.y, v.y, n.y, 0.0f,
                 u.z, v.z, n.z, 0.0f,
                 -dot( u, position ), -dot( v, position ), -dot( n, position ),
                 1.0f );
}

///
// Get the projection matrix of the camera.
//
// @return the projection matrix
///
mat4 Camera::getProjectionMat() {
    mat4 Projection = mat4( 0.0f );
    float tanHalfFov = tan( fov * float( M_PI ) / 360.0f );

    Projection[ 0 ][ 0 ] = 1.0f / ( aspect * tanHalfFov );
    Projection[ 1 ][ 1 ] = 1.0f / ( tanHalfFov );
    Projection[ 2 ][ 3 ] = -1.0f;
    Projection[ 2 ][ 2 ] = -( zfar + znear ) / ( zfar - znear );
    Projection[ 3 ][ 2 ] = -( 2.0f * zfar * znear ) / ( zfar - znear );

    return Projection;
}
